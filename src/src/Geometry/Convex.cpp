int turn(cp a, cp b, cp c) {
    return sgn((b - a) ^ (c - a));
}

vp convex(vp p) {
    if (p.size() < 2) return p;
    std::sort(p.begin(), p.end());
    int n = p.size(), cnt = 0;
    vp con({p[0]});
    for (int i = 1; i < n; ++i) {
        while (cnt > 0 && turn(con[cnt - 1], con[cnt], p[i]) < 0)
            --cnt, con.pop_back(); // 改为 <= 0 可删除共线边界点
        ++cnt, con.push_back(p[i]);
    }
    int fixed = cnt;
    for (int i = n - 2; i >= 0; --i) {
        while (cnt > fixed && turn(con[cnt - 1], con[cnt], p[i]) < 0)
            --cnt, con.pop_back(); // 改为 <= 0 可删除共线边界点
        ++cnt, con.push_back(p[i]);
    }
    con.pop_back();
    return con;
}

vp minkowski(vp p1, vp p2) {
    if (p1.empty() || p2.empty()) return {};
    int n1 = p1.size(), n2 = p2.size();
    vp ret;
    if (n1 == 1) {
        for (cp p : p2) ret.push_back(p1[0] + p);
        return ret;
    }
    if (n2 == 1) {
        for (cp p : p1) ret.push_back(p + p2[0]);
        return ret;
    }
    p1.push_back(p1[0]), p1.push_back(p1[1]);
    p2.push_back(p2[0]), p2.push_back(p2[1]);
    ret.push_back(p1[0] + p2[0]);
    int i1 = 0, i2 = 0;
    while (i1 < n1 || i2 < n2) {
        ld cross = (p1[i1 + 1] - p1[i1]) ^ (p2[i2 + 1] - p2[i2]);
        if (i2 == n2 || (i1 < n1 && sgn(cross) > 0))
            ret.push_back(p1[++i1] + p2[i2]);
        else
            ret.push_back(p1[i1] + p2[++i2]);
    }
    ret.pop_back();
    return ret;
}

struct convex_chain {
    int n;
    vp a, upper, lower;

    convex_chain(cvp points): n(points.size()), a(points) {
        int k = 0;
        for (int i = 1; i < n; ++i)
            if (a[i] > a[k]) k = i;
        for (int i = 0; i <= k; ++i) lower.push_back(a[i]);
        for (int i = k; i < n; ++i) upper.push_back(a[i]);
        upper.push_back(a[0]);
    }
};

// 以下查询均要求凸包 a 逆时针排列，且 n = a.size()。
int n;
vp a;

bool inside(cp u) { // 点在凸包内
    int l = 1, r = n - 2;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (turn(a[0], a[mid], u) >= 0) l = mid;
        else r = mid - 1;
    }
    return turn(a[0], a[l], u) >= 0
            && turn(a[l], a[l + 1], u) >= 0
            && turn(a[l + 1], a[0], u) >= 0;
}

int search(auto f) { // 凸包求极值，需要 C++20
    int l = 0, r = n - 1;
    int d = f(a[r], a[l]) ? (std::swap(l, r), -1) : 1;
    while (d * (r - l) > 1) {
        int mid = (l + r) / 2;
        if (f(a[mid], a[l]) && f(a[mid], a[mid - d])) l = mid;
        else r = mid;
    }
    return l;
}

std::pair<int, int> get_tan(cp u) { // 求严格在凸包外的点的两条切线
    return {
        search([&](cp x, cp y) { return turn(u, y, x) > 0; }),
        search([&](cp x, cp y) { return turn(u, x, y) > 0; })
    };
}

point at(int i) { return a[i % n]; }

int inter(cp u, cp v, int l, int r) {
    int side = turn(u, v, at(l));
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (side == turn(u, v, at(mid))) l = mid;
        else r = mid;
    }
    return l % n;
}

bool get_inter(cp u, cp v, int &i, int &j) { // 求直线与凸包交点所在边
    int p0 = search([&](cp x, cp y) {
        return ((v - u) ^ (x - u)) < ((v - u) ^ (y - u));
    });
    int p1 = search([&](cp x, cp y) {
        return ((v - u) ^ (x - u)) > ((v - u) ^ (y - u));
    });
    if (turn(u, v, a[p0]) * turn(u, v, a[p1]) < 0) {
        if (p0 > p1) std::swap(p0, p1);
        i = inter(u, v, p0, p1);
        j = inter(u, v, p1, p0 + n);
        return true;
    }
    return false;
}

ld near(cp u, int l, int r) {
    if (l > r) r += n;
    int side = sgn((u - at(l)) * (at(l + 1) - at(l)));
    ld ret = point_to_segment(u, line(at(l), at(l + 1)));
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (side == sgn((u - at(mid)) * (at(mid + 1) - at(mid))))
            l = mid;
        else
            r = mid;
    }
    return std::min(ret, point_to_segment(u, line(at(l), at(l + 1))));
}

ld get_near(cp u) { // 求凸包外点到凸包最近点
    if (inside(u)) return 0;
    auto [x, y] = get_tan(u);
    return std::min(near(u, x, y), near(u, y, x));
}

struct hull { // 动态上凸壳，从左到右维护；适用于整数坐标
    std::set<point> a;
    ld total;

    hull(): total(0) {}

    ld calc(auto it) {
        auto u = it == a.begin() ? a.end() : std::prev(it);
        auto v = std::next(it);
        ld ret = 0;
        if (u != a.end()) ret += *u ^ *it;
        if (v != a.end()) ret += *it ^ *v;
        if (u != a.end() && v != a.end()) ret -= *u ^ *v;
        return ret;
    }

    void insert(point p) {
        if (a.empty()) {
            a.insert(p);
            return;
        }
        auto it = a.lower_bound(p);
        bool out;
        if (it == a.begin()) out = p < *it;
        else if (it == a.end()) out = true;
        else out = turn(*std::prev(it), *it, p) > 0;
        if (!out) return;
        while (it != a.begin()) {
            auto old = std::prev(it);
            if (old == a.begin() || turn(*std::prev(old), *old, p) < 0)
                break;
            erase(old);
        }
        while (it != a.end()) {
            auto next = std::next(it);
            if (next == a.end() || turn(p, *it, *next) < 0)
                break;
            erase(it), it = next;
        }
        total += calc(a.insert(p).first);
    }

    void erase(auto it) {
        total -= calc(it);
        a.erase(it);
    }
};

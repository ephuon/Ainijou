int turn(cp a, cp b, cp c) { // 有向转向：a->b->c 左转 1，右转 -1，共线 0
    return sgn((b - a) ^ (c - a));
}

vp convex(vp p) { // Andrew 算法求二维凸包，O(n log n)
    // 输入应先去重，且不应全部共线；否则可能保留重复顶点或往返经过共线点。
    // 返回凸包顶点的逆时针序列：从字典序最小点开始，首点不会在末尾重复。
    // 当前使用 < 0，保留凸包边上的共线点；改为 <= 0 可只保留边的端点。
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

vp minkowski(vp p1, vp p2) { // 两个凸多边形的 Minkowski 和，O(n1+n2)
    // 两个输入都应按逆时针排列、从字典序最小点开始，且末尾不重复首点；
    // 相邻点不可重复。最好先删除同一直线边上的中间点。
    // 任一输入为空时返回空；点与多边形相加会直接平移另一个多边形。
    // 返回顺序与输入约定相同；平行同向边可能使结果含冗余共线点。
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

struct convex_chain { // 把凸包按字典序最小点、最大点拆成上下两条单调链
    int n;
    vp a, upper, lower;

    convex_chain(cvp points): n(points.size()), a(points) {
        // 要求 points 至少含 2 点、逆时针排列、以字典序最小点开头且不重复首点。
        // lower 从最小点走到最大点，upper 从最大点走回最小点；两条链共享两端点。
        int k = 0;
        for (int i = 1; i < n; ++i)
            if (a[i] > a[k]) k = i;
        for (int i = 0; i <= k; ++i) lower.push_back(a[i]);
        for (int i = k; i < n; ++i) upper.push_back(a[i]);
        upper.push_back(a[0]);
    }
};

// ==================== 静态凸包查询 ====================
// 以下查询共享全局 a、n。要求 n >= 3，a 是逆时针严格凸包，
// 不含重复点、连续共线点，且 a[n-1] 与 a[0] 之间也是一条有效凸包边。
int n;
vp a;

bool inside(cp u) { // 点 u 是否在凸包内部或边界上，O(log n)
    // 三条 turn 均使用 >= 0，因此凸包边界计作内部。
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

int search(auto f) { // 在循环凸包序列上二分满足比较器 f 的极值点，O(log n)
    // 使用 abbreviated function template，需要 C++20。
    // f(x,y) 应表示“x 比 y 更优”，且目标值沿凸包边界满足单峰性；
    // 若极值不唯一，本函数只保证返回其中一个满足二分过程的顶点。
    int l = 0, r = n - 1;
    int d = f(a[r], a[l]) ? (std::swap(l, r), -1) : 1;
    while (d * (r - l) > 1) {
        int mid = (l + r) / 2;
        if (f(a[mid], a[l]) && f(a[mid], a[mid - d])) l = mid;
        else r = mid;
    }
    return l;
}

std::pair<int, int> get_tan(cp u) { // 外点 u 到凸包的两个切点下标，O(log n)
    // 要求 u 严格位于凸包外，且切点为顶点；u 在边界上时结果没有定义。
    // 若需要支持 a[n-1]->a[0] 边上的点，必须单独处理该边界情形。
    return {
        search([&](cp x, cp y) { return turn(u, y, x) > 0; }),
        search([&](cp x, cp y) { return turn(u, x, y) > 0; })
    };
}

point at(int i) { // 循环访问凸包顶点；只支持 i >= 0
    return a[i % n];
}

int inter(cp u, cp v, int l, int r) { // 在展开区间 [l,r] 二分直线 uv 穿过的凸包边
    // 要求 l < r，端点位于直线两侧，且区间内侧别只发生一次变化；
    // 返回边 [at(ans),at(ans+1)] 的起点下标。直线经过顶点/重合边时需另行处理。
    int side = turn(u, v, at(l));
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (side == turn(u, v, at(mid))) l = mid;
        else r = mid;
    }
    return l % n;
}

bool get_inter(cp u, cp v, int &i, int &j) { // 求无限直线 uv 穿过的两条凸包边
    // 要求 u != v。仅当凸包在直线两侧均有严格顶点时返回 true，并写入边下标 i、j；
    // 相离、相切或与凸包边共线时返回 false。若直线严格穿过凸包且恰经过顶点，
    // 仍可返回 true，但该顶点相邻的两条边都合法，本函数只会给出其中一条。
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

ld near(cp u, int l, int r) { // 点 u 到凸包边链 [l,r] 的最短距离，O(log n)
    // l、r 是两切点下标；允许 l > r，此时区间跨过下标 n-1 到 0。
    // 要求该链上“投影落在边前/后”的符号至多改变一次。
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

ld get_near(cp u) { // 点 u 到闭凸包的最短距离，O(log n)
    // 边界和内部返回 0；外部点先求两切点，再分别查询两条边链。
    if (inside(u)) return 0;
    auto [x, y] = get_tan(u);
    return std::min(near(u, x, y), near(u, y, x));
}

// ==================== 单点插入动态上凸壳 ====================
struct hull { // 按 x/y 字典序从左到右维护上凸壳
    // 只支持插入，不支持恢复被淘汰的旧点；几何判断用 eps，而 set 排序是精确比较，
    // 因此更适合整数坐标，或确保浮点坐标彼此有明显间隔的场景。
    // 同一 x 可保留竖直端边；若题意要求每个 x 只留最高点，应在插入前单独合并。
    std::set<point> a; // 壳上的点；共线中间点会被删除
    ld total;          // 相邻点叉积之和，不包含末点到首点的闭合边

    hull(): total(0) {}

    ld calc(auto it) { // 迭代器 it 对 total 的局部贡献
        // 要求 it 是 a 中有效迭代器；使用 C++20 abbreviated function template。
        auto u = it == a.begin() ? a.end() : std::prev(it);
        auto v = std::next(it);
        ld ret = 0;
        if (u != a.end()) ret += *u ^ *it;
        if (v != a.end()) ret += *it ^ *v;
        if (u != a.end() && v != a.end()) ret -= *u ^ *v;
        return ret;
    }

    void insert(point p) { // 插入点 p；若 p 位于当前上凸壳下方/边界内则忽略
        // 重复点会被忽略；若 p 在现有共线边的外侧延长线上，会保留更外侧端点。
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

    void erase(auto it) { // 删除壳上已有点并同步 total，仅供维护过程调用
        // 要求 it 有效且属于 a；外部直接调用可能破坏上凸壳不变量。
        total -= calc(it);
        a.erase(it);
    }
};

struct circle {
    point c;
    ld r;

    circle(cp c, const ld &r = 0): c(c), r(r) {}
    circle(cc a): c(a.c), r(a.r) {}
    circle(cp a, cp b) {
        c = (a + b) / 2;
        r = (a - c).len();
    }
    circle(cp x, cp y, cp z) { // 注意三点共线
        point p(y - x), q(z - x);
        point s((p * p) / 2, (q * q) / 2);
        ld d = p ^ q;
        p = point(s ^ point(p.y, q.y), point(p.x, q.x) ^ s) / d;
        c = x + p, r = p.len();
    }
};

bool in_circle(cp a, cc b) {
    return sgn((b.c - a).len() - b.r) <= 0;
}

circle min_circle(vp p) { // O(n)，要求 p 非空
    std::shuffle(p.begin(), p.end(), rnd);
    int n = p.size(), i, j, k;
    circle ret(p[0], 0);
    for (i = 1; i < n; ++i)
        if (!in_circle(p[i], ret))
            for (ret = circle(p[i], p[0]), j = 1; j < i; ++j)
                if (!in_circle(p[j], ret))
                    for (ret = circle(p[i], p[j]), k = 0; k < j; ++k)
                        if (!in_circle(p[k], ret))
                            ret = circle(p[i], p[j], p[k]);
    return ret;
}

vp lc_intersection(cl l, cc c) {
    ld x = point_to_line(c.c, l);
    if (sgn(x - c.r) > 0) return {};
    x = std::sqrt(std::max<ld>(0, c.r * c.r - x * x));
    point p(project_to_line(c.c, l));
    if (sgn(x) == 0) return {p};
    point d = (l.t - l.s).unit();
    return {p + x * d, p - x * d};
}

ld cc_intersection_area(cc a, cc b) {
    ld d = (a.c - b.c).len();
    if (sgn(d - a.r - b.r) >= 0) return 0;
    if (sgn(d - std::abs(a.r - b.r)) <= 0) {
        ld r = std::min(a.r, b.r);
        return pi * r * r;
    }
    ld x = (d * d + a.r * a.r - b.r * b.r) / (2 * d);
    ld t1 = std::acos(std::clamp(x / a.r, -1.0L, 1.0L));
    ld t2 = std::acos(std::clamp((d - x) / b.r, -1.0L, 1.0L));
    return a.r * a.r * t1 + b.r * b.r * t2
            - d * a.r * std::sin(t1);
}

vp cc_intersection(cc a, cc b) {
    ld d = (a.c - b.c).len();
    if (a.c == b.c || sgn(d - a.r - b.r) > 0
            || sgn(d - std::abs(a.r - b.r)) < 0)
        return {};
    point dir = (b.c - a.c).unit();
    ld x = (d * d + a.r * a.r - b.r * b.r) / (2 * d);
    ld h = std::sqrt(std::max<ld>(0, a.r * a.r - x * x));
    if (sgn(h) == 0) return {a.c + x * dir};
    return {a.c + x * dir + h * dir.rot90(),
            a.c + x * dir - h * dir.rot90()};
}

vp tangent(cp a, cc b) { // 点到圆的切点
    return cc_intersection(b, circle(a, b.c));
}

std::vector<line> tangent(cc a, cc b, int f) {
    // f = 1：外公切线；f = -1：内公切线
    ld d = (b.c - a.c).len();
    int relation = sgn(std::abs((b.r - f * a.r) / d) - 1);
    if (relation > 0) return {};
    if (relation == 0) {
        point p = a.c - sgn(b.r - f * a.r) * f * a.r
                * (b.c - a.c).unit();
        return {line(p, p + (b.c - a.c).rot90())};
    }
    ld theta = std::asin(std::clamp(f * (b.r - f * a.r) / d,
                                    -1.0L, 1.0L));
    point dir = (b.c - a.c).unit();
    point dir1 = dir.rot(theta + pi / 2);
    point dir2 = dir.rot(-theta - pi / 2);
    return {line(a.c + a.r * dir1, b.c + f * b.r * dir1),
            line(a.c + a.r * dir2, b.c + f * b.r * dir2)};
}

struct circle { // 圆由圆心 c 与半径 r 表示
    point c;
    ld r; // 以下所有圆算法均要求 r >= 0

    circle(cp c, const ld &r = 0): c(c), r(r) {} // 指定圆心、半径
    circle(cc a): c(a.c), r(a.r) {}              // 拷贝构造
    circle(cp a, cp b) { // 以线段 ab 为直径构圆；a == b 时为点圆
        c = (a + b) / 2;
        r = (a - c).len();
    }
    circle(cp x, cp y, cp z) { // 三点外接圆；要求三点不共线
        // 三点共线或 eps 意义下近似共线时 d 接近 0，结果无效。
        point p(y - x), q(z - x);
        point s((p * p) / 2, (q * q) / 2);
        ld d = p ^ q;
        p = point(s ^ point(p.y, q.y), point(p.x, q.x) ^ s) / d;
        c = x + p, r = p.len();
    }
};

bool in_circle(cp a, cc b) { // 点 a 是否在圆 b 内部或边界上
    // 边界按 eps 计入圆内；要求 b.r >= 0。
    return sgn((b.c - a).len() - b.r) <= 0;
}

circle min_circle(vp p) { // 随机增量法求最小覆盖圆，期望 O(n)
    // 要求 p 非空；允许重复点。三点构圆仍要求相关三点不共线，
    // 若输入可能触发共线三点构圆，应为该情形补充以最远点对为直径的特判。
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

vp lc_intersection(cl l, cc c) { // 无限直线 l 与圆 c 的交点
    // 要求 l 不退化且 c.r >= 0。相离返回空，外切返回 1 点，相交返回 2 点。
    // 两交点依次位于垂足沿 (l.t-l.s) 正方向、负方向的一侧。
    ld x = point_to_line(c.c, l);
    if (sgn(x - c.r) > 0) return {};
    x = std::sqrt(std::max<ld>(0, c.r * c.r - x * x));
    point p(project_to_line(c.c, l));
    if (sgn(x) == 0) return {p};
    point d = (l.t - l.s).unit();
    return {p + x * d, p - x * d};
}

ld cc_intersection_area(cc a, cc b) { // 两个闭圆盘交集的面积
    // 相离或外切返回 0；内含或内切返回小圆面积；一般相交返回两弓形面积之和。
    // 同心圆与点圆均可处理，但半径必须非负。
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

vp cc_intersection(cc a, cc b) { // 两圆圆周的有限交点
    // 相离、内含但不内切、同心圆均返回空；注意重合圆有无穷交点，也以空表示。
    // 相切返回 1 点，相交返回 2 点；两点分别在 a.c->b.c 的左侧、右侧。
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

vp tangent(cp a, cc b) { // 过点 a 作圆 b 的切线，返回圆上的切点
    // a 在圆内返回空，在圆上返回 a，严格在圆外返回两个切点。
    // 例外：若 b 是点圆且 a == b.c，重合圆的无穷交点约定使本函数返回空。
    return cc_intersection(b, circle(a, b.c));
}

std::vector<line> tangent(cc a, cc b, int f) { // 两圆公切线
    // 仅支持 f = 1（外公切线）或 f = -1（内公切线）。
    // 返回 0/1/2 条有向线，每条从圆 a 的切点指向圆 b 的切点。
    // 要求两圆圆心不同且半径非负；同心圆的 0 条或无穷多条切线不由本函数处理。
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

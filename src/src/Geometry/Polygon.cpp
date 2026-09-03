vp poly_cut(vp p, cl l) { // 用有向直线 l 裁剪凸多边形 p，O(n)
    // 保留 l.s->l.t 左侧及直线上的点，返回值沿用 p 的顶点顺序且不重复首点。
    // p 可顺时针或逆时针，但必须是单个凸多边形；一般凹多边形裁剪后可能不连通，
    // 本函数的单个点序列无法表示多个连通分量。要求 l 不退化。
    // 空输入返回空；边与裁剪线严格相交时插入唯一交点，线上的原端点直接保留。
    if (p.empty()) return {};
    vp ret;
    int n = p.size();
    p.push_back(p[0]);
    for (int i = 0; i < n; ++i) {
        if (sgn((p[i] - l.s) ^ (l.t - l.s)) <= 0)
            ret.push_back(p[i]);
        if (two_side(p[i], p[i + 1], l))
            ret.push_back(ll_intersection(l, line(p[i], p[i + 1])));
    }
    return ret;
}

ld poly_area(cvp p) { // 简单多边形面积，O(n)
    // 顺/逆时针均返回非负面积；少于 3 点返回 0。
    // 自交多边形得到的是有向面积绝对值，不一定等于各区域几何面积之和。
    ld area = 0;
    int n = p.size();
    for (int i = 0, j = n - 1; i < n; j = i++) area += p[i] ^ p[j];
    return std::abs(area) / 2;
}

ld vector_angle(cp u, cp v) { // 两个非零向量的无向小夹角，范围 [0, pi]
    // 使用单位向量弦长公式；任一向量为零时 unit() 会除以 0，本函数不适用。
    ld chord = (u.unit() - v.unit()).len();
    return 2 * std::asin(std::clamp(chord / 2, 0.0L, 1.0L));
}

ld sector_triangle_area(cp s, cp t, ld r) { // 圆心在原点时，一条边对交面积的贡献
    // 要求 r >= 0，s、t 非零且 s^t >= 0；返回圆盘与三角形 O-s-t 交集的二倍面积。
    // 若 s^t < 0，应交换 s、t 后调用并在外层减去结果。
    // 线段不穿过圆内部时贡献为扇形；穿过时拆为弦三角形与两侧扇形。
    ld theta = vector_angle(s, t);
    ld distance = point_to_segment(point(), line(s, t));
    if (sgn(distance - r) >= 0) return theta * r * r;
    vp intersections = lc_intersection(line(s, t), circle(point(), r));
    point u = intersections.front(), v = intersections.back();
    point lo = sgn(s ^ u) >= 0 ? u : s;
    point hi = sgn(v ^ t) >= 0 ? v : t;
    return (lo ^ hi) + (theta - vector_angle(lo, hi)) * r * r;
}

ld polygon_circle_intersection_area(cvp p, cc c) { // 简单多边形与圆盘交集面积，O(n)
    // p 可顺时针或逆时针，末尾不要重复首点；空多边形返回 0，圆半径须非负。
    // 当前辅助函数要求每个顶点均不与圆心 c 重合；若重合，应先删去该零长度向量顶点
    // 或单独处理相邻边，否则 vector_angle() 中单位化零向量会产生无效值。
    // 对每条边按叉积方向累加/减去贡献，最终取绝对值，因此返回非负面积。
    ld ret = 0;
    for (int i = 0; i < (int)p.size(); ++i) {
        point u = p[i] - c.c;
        point v = p[(i + 1) % p.size()] - c.c;
        int side = sgn(u ^ v);
        if (side > 0) ret += sector_triangle_area(u, v, c.r);
        else if (side < 0) ret -= sector_triangle_area(v, u, c.r);
    }
    return std::abs(ret) / 2;
} // 对简单多边形，p 逆时针时未取绝对值的 ret 为正

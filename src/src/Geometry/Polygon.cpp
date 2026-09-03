vp poly_cut(vp p, cl l) { // 直线切多边形，返回左侧图形端点，O(n)
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

ld poly_area(cvp p) {
    ld area = 0;
    int n = p.size();
    for (int i = 0, j = n - 1; i < n; j = i++) area += p[i] ^ p[j];
    return std::abs(area) / 2;
}

ld vector_angle(cp u, cp v) {
    ld chord = (u.unit() - v.unit()).len();
    return 2 * std::asin(std::clamp(chord / 2, 0.0L, 1.0L));
}

ld sector_triangle_area(cp s, cp t, ld r) { // 返回二倍有向面积
    ld theta = vector_angle(s, t);
    ld distance = point_to_segment(point(), line(s, t));
    if (sgn(distance - r) >= 0) return theta * r * r;
    vp intersections = lc_intersection(line(s, t), circle(point(), r));
    point u = intersections.front(), v = intersections.back();
    point lo = sgn(s ^ u) >= 0 ? u : s;
    point hi = sgn(v ^ t) >= 0 ? v : t;
    return (lo ^ hi) + (theta - vector_angle(lo, hi)) * r * r;
}

ld polygon_circle_intersection_area(cvp p, cc c) {
    ld ret = 0;
    for (int i = 0; i < (int)p.size(); ++i) {
        point u = p[i] - c.c;
        point v = p[(i + 1) % p.size()] - c.c;
        int side = sgn(u ^ v);
        if (side > 0) ret += sector_triangle_area(u, v, c.r);
        else if (side < 0) ret -= sector_triangle_area(v, u, c.r);
    }
    return std::abs(ret) / 2;
} // p 逆时针时，未取绝对值的 ret 为正

// 本节前三个“心”均要求 a、b、c 构成非退化三角形（互异且不共线）。

point incenter(cp a, cp b, cp c) { // 三角形内心：三条内角平分线交点
    // 按对边长度加权；退化三角形没有通常意义下的内心。
    ld ab = (a - b).len(), bc = (b - c).len(), ca = (c - a).len();
    return (bc * a + ca * b + ab * c) / (ab + bc + ca);
}

point circumcenter(cp a, cp b, cp c) { // 三角形外心：三边垂直平分线交点
    // p^q 是分母；三点共线或近似共线时分母为 0/过小，结果无效或误差很大。
    point p = b - a, q = c - a;
    point s((p * p) / 2, (q * q) / 2);
    ld d = p ^ q;
    return a + point(s ^ point(p.y, q.y), point(p.x, q.x) ^ s) / d;
}

point orthocenter(cp a, cp b, cp c) { // 三角形垂心：三条高的交点
    // 使用 H = A+B+C-2O，其中 O 为外心；退化限制与 circumcenter 相同。
    return a + b + c - 2.0L * circumcenter(a, b, c);
}

point fermat_point(cp a, cp b, cp c) { // 使 |A-x|+|B-x|+|C-x| 最小的费马点
    // 有重合点时返回重复出现的点；某内角大于 120 度时直接返回该顶点。
    // 内角恰为 120 度时走后续构造，精确运算下交点仍是该顶点。
    // 其余情况构造两个向外的正三角形边并求交；三点顺/逆时针分别处理。
    // 三点共线且互异时，钝角（180 度）分支会返回位于中间的点。
    if (a == b) return a;
    if (b == c) return b;
    if (c == a) return c;
    ld ab = (a - b).len(), bc = (b - c).len(), ca = (c - a).len();
    ld cosa = (b - a) * (c - a) / ab / ca;
    ld cosb = (a - b) * (c - b) / ab / bc;
    ld cosc = (b - c) * (a - c) / ca / bc;
    ld angle60 = pi / 3;
    point ret;
    if (sgn(cosa + 0.5L) < 0)
        ret = a;
    else if (sgn(cosb + 0.5L) < 0)
        ret = b;
    else if (sgn(cosc + 0.5L) < 0)
        ret = c;
    else if (turn(a, b, c) < 0)
        ret = ll_intersection(line(a, b + (c - b).rot(angle60)),
                              line(b, c + (a - c).rot(angle60)));
    else
        ret = ll_intersection(line(a, c + (b - c).rot(angle60)),
                              line(c, b + (a - b).rot(angle60)));
    return ret;
}

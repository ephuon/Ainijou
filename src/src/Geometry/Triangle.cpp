point incenter(cp a, cp b, cp c) { // 内心
    ld ab = (a - b).len(), bc = (b - c).len(), ca = (c - a).len();
    return (bc * a + ca * b + ab * c) / (ab + bc + ca);
}

point circumcenter(cp a, cp b, cp c) { // 外心
    point p = b - a, q = c - a;
    point s((p * p) / 2, (q * q) / 2);
    ld d = p ^ q;
    return a + point(s ^ point(p.y, q.y), point(p.x, q.x) ^ s) / d;
}

point orthocenter(cp a, cp b, cp c) { // 垂心
    return a + b + c - 2.0L * circumcenter(a, b, c);
}

point fermat_point(cp a, cp b, cp c) { // 费马点
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
} // 最小化 |A-x| + |B-x| + |C-x|

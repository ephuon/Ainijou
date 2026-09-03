int half(cp a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : 0;
}

bool turn_left(cl a, cl b, cl c) {
    point p = ll_intersection(b, c);
    return sgn((a.t - a.s) ^ (p - a.s)) > 0;
}

bool parallel(cl a, cl b) {
    return sgn((a.t - a.s) ^ (b.t - b.s)) == 0;
}

bool line_angle_cmp(cl a, cl b) {
    int side = half(a.t - a.s) - half(b.t - b.s);
    int direction = sgn((a.t - a.s) ^ (b.t - b.s));
    if (direction == 0 && side == 0)
        return turn(a.s, a.t, b.t) < 0;
    return side != 0 ? side > 0 : direction > 0;
}

std::vector<point> hpi(std::vector<line> halfplanes) {
    std::sort(halfplanes.begin(), halfplanes.end(), line_angle_cmp);
    std::vector<line> q(halfplanes.size(), line(point(), point()));
    int l = 0, r = -1;
    for (cl current : halfplanes) {
        while (l < r && !turn_left(current, q[r - 1], q[r])) --r;
        while (l < r && !turn_left(current, q[l], q[l + 1])) ++l;
        if (l <= r && parallel(current, q[r])) continue;
        q[++r] = current;
    }
    while (r - l > 1 && !turn_left(q[l], q[r - 1], q[r])) --r;
    while (r - l > 1 && !turn_left(q[r], q[l], q[l + 1])) ++l;
    if (r - l < 2) return {};
    std::vector<point> ret(r - l + 1);
    for (int i = l; i <= r; ++i)
        ret[i - l] = ll_intersection(q[i], q[i == r ? l : i + 1]);
    return ret;
}
// 空集会在队列里留下一个开区域，开区域会被判定为空集。
// 为保证正确性，一定要加足够大的框，尽可能避免零面积区域。
// 若必须保留零面积区域边缘，需要仔细调整 turn_left 的实现。

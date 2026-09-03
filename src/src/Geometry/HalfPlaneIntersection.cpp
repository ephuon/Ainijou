// 每条有向直线均表示其左侧可行半平面；正面积结果的边界由这些直线给出。

int half(cp a) { // 极角排序用的半平面编号：上半平面 1，下半平面 0
    // 正 x 轴归入上半平面，负 x 轴归入下半平面；要求 a 是非零方向向量。
    // 这里对 y == 0 使用精确比较，以保持排序比较器的严格弱序性质。
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : 0;
}

bool turn_left(cl a, cl b, cl c) { // 直线 b、c 的交点是否严格位于 a 的左侧
    // 要求 b、c 不平行且三条直线均不退化；边界点返回 false。
    point p = ll_intersection(b, c);
    return sgn((a.t - a.s) ^ (p - a.s)) > 0;
}

bool parallel(cl a, cl b) { // 两条直线的方向是否在 eps 意义下平行
    // 同向和反向均返回 true；退化直线也会被判为平行，故输入不得退化。
    return sgn((a.t - a.s) ^ (b.t - b.s)) == 0;
}

bool line_angle_cmp(cl a, cl b) { // 按方向极角排序半平面边界
    // 同向平行时把更靠左、也就是约束更强的直线排在前面，供 hpi 去重。
    // 要求输入直线不退化；近似平行的方向应有足够数值间隔，避免 eps 比较破坏排序稳定性。
    int side = half(a.t - a.s) - half(b.t - b.s);
    int direction = sgn((a.t - a.s) ^ (b.t - b.s));
    if (direction == 0 && side == 0)
        return turn(a.s, a.t, b.t) < 0;
    return side != 0 ? side > 0 : direction > 0;
}

std::vector<point> hpi(std::vector<line> halfplanes) { // 左半平面交，O(n log n)
    // 每条线均须不退化，方向按“可行域在左侧”给出。建议先加入足够大的逆时针外框，
    // 将无界区域截成有界区域；否则空集与无界/开区域都可能以空向量表示。
    // 返回非空有界交集的顶点循环序列，不重复首点；平行同向约束只保留最强者。
    // 内部判定使用严格左转：正面积区域仍返回边界顶点；零面积交集（点或线段）会被判空。
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
// 注意：若不加外框，队列可能留下无法闭合的开区域，最终同样返回空。

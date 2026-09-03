struct line { // 有向直线 s -> t；也按调用场景表示线段 [s,t] 或射线 s->t
    point s, t; // s 是起点，t 决定方向；允许存储退化线段 s == t

    line (cp a, cp b) : s(a), t(b) {} // 由两个端点构造
    line (cl l): s(l.s), t(l.t) {}    // 拷贝构造
};
bool point_on_line(cp a, cl l) { // 点 a 在无限直线 l 上；要求 l.s != l.t
    return sgn((a - l.s) ^ (l.t - l.s)) == 0;
}
bool point_on_segment(cp a, cl l) { // 点 a 在线段 [l.s,l.t] 上，包含端点
    // l 退化为点时，当前实现以 (a-l.s).len2() <= eps 作为重合标准。
    return sgn((a - l.s) ^ (l.t - l.s)) == 0 && sgn((a - l.s) * (a - l.t)) <= 0;
}
bool two_side(cp a, cp b, cl l) { // a、b 严格位于无限直线 l 两侧
    // 点落在直线上或 l 退化时返回 false。
    return sgn((a - l.s) ^ (a - l.t)) * sgn((b - l.s) ^ (b - l.t)) < 0;
}
bool intersection_judge_strict(cl a, cl b) { // 线段 a、b 严格相交于各自内部
    // 端点相交、共线重叠或任一线段退化均返回 false。
    return two_side(a.s, a.t, b) && two_side(b.s, b.t, a);
}
bool intersection_judge(cl a, cl b) { // 闭线段 a、b 是否有公共点
    // 包含端点相交、共线重叠及退化线段相交。
    return point_on_segment(a.s, b) || point_on_segment(a.t, b) ||
             point_on_segment(b.s, a) || point_on_segment(b.t, a) ||
                intersection_judge_strict(a, b);
}
point ll_intersection(cl a, cl b) { // 两条无限直线的唯一交点，不检查线段范围
    // 要求两直线均不退化且不平行；平行或重合时分母为 0，返回值无效。
    ld s1 = (a.t - a.s) ^ (b.s - a.s), s2 = (a.t - a.s) ^ (b.t - a.s);
    return (s2 * b.s - s1 * b.t) / (s2 - s1);
}
bool point_on_ray(cp a, cl b) { // 点 a 在射线 b.s -> b.t 上，包含起点
    // 要求 b.s != b.t；退化射线会令任意点都通过当前判定。
    return sgn((a - b.s) ^ (b.t - b.s)) == 0 && sgn((a - b.s) * (b.t - b.s)) >= 0;
}
bool ray_intersection_judge(cl a, cl b) { // 两条射线是否在唯一交点处相交
    // 包含射线起点；要求方向非零且所在直线不平行，共线射线不适用。
    point p(ll_intersection(a, b));
    return sgn((p - a.s) * (a.t - a.s)) >= 0 && sgn((p - b.s) * (b.t - b.s)) >= 0;
}
ld point_to_line(cp a, cl b) { // 点 a 到无限直线 b 的欧氏距离
    // 要求 b.s != b.t，否则分母为 0。
    return std::abs((b.t - b.s) ^ (a - b.s)) / (b.t - b.s).len();
}
point project_to_line(cp a, cl b) { // 点 a 在无限直线 b 上的正交投影（垂足）
    // 要求 b.s != b.t，否则方向向量长度平方为 0。
    return b.s + (a - b.s) *
    (b.t - b.s) / (b.t - b.s).len2() * (b.t - b.s);
}
ld point_to_segment(cp a, cl b) { // 点 a 到闭线段 [b.s,b.t] 的最短距离
    // 显式处理退化线段；垂足在线段内（含端点）时返回垂距，否则返回端点距离。
    if (b.s == b.t) return (a - b.s).len();
    if (sgn((a - b.s) * (b.t - b.s)) * sgn((a - b.t) * (b.t - b.s)) <= 0)
        return std::abs((b.t - b.s) ^ (a - b.s)) / (b.t - b.s).len();
    return std::min((a - b.s).len(), (a - b.t).len());
}

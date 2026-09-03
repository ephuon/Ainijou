struct line {
    point s, t;

    line (cp a, cp b) : s(a), t(b) {}
    line (cl l): s(l.s), t(l.t) {}
};
bool point_on_line(cp a, cl l) { // 点在直线上
    return sgn((a - l.s) ^ (l.t - l.s)) == 0;
}
bool point_on_segment(cp a, cl l) { // 点在线段上（包含端点）
    return sgn((a - l.s) ^ (l.t - l.s)) == 0 && sgn((a - l.s) * (a - l.t)) <= 0;
}
bool two_side(cp a, cp b, cl l) { // a 和 b 严格在直线两端
    return sgn((a - l.s) ^ (a - l.t)) * sgn((b - l.s) ^ (b - l.t)) < 0;
}
bool intersection_judge_strict(cl a, cl b) { // **线段** a 和 b 严格相交
    return two_side(a.s, a.t, b) && two_side(b.s, b.t, a);
}
bool intersection_judge(cl a, cl b) { // **线段** a 和 b 相交
    return point_on_segment(a.s, b) || point_on_segment(a.t, b) ||
             point_on_segment(b.s, a) || point_on_segment(b.t, a) || 
                intersection_judge_strict(a, b);
}
point ll_intersection(cl a, cl b) { // 两线段？直线？交点？ 万一 s2 == s1呢？
    ld s1 = (a.t - a.s) ^ (b.s - a.s), s2 = (a.t - a.s) ^ (b.t - a.s);
    return (s2 * b.s - s1 * b.t) / (s2 - s1);
}
bool point_on_ray(cp a, cl b) { 
    return sgn((a - b.s) ^ (b.t - b.s)) == 0 && sgn((a - b.s) * (b.t - b.s)) >= 0;
}
bool ray_intersection_judge(cl a, cl b) {
    point p(ll_intersection(a, b));
    return sgn((p - a.s) * (a.t - a.s)) >= 0 && sgn((p - b.s) * (b.t - b.s)) >= 0;
}
ld point_to_line(cp a, cl b) {
    return std::abs((b.t - b.s) ^ (a - b.s)) / (b.t - b.s).len();
}
point project_to_line(cp a, cl b) { 
    return b.s + (a - b.s) *
    (b.t - b.s) / (b.t - b.s).len2() * (b.t - b.s);
} 
ld point_to_segment(cp a, cl b) {
    if (b.s == b.t) return (a - b.s).len();
    if (sgn((a - b.s) * (b.t - b.s)) * sgn((a - b.t) * (b.t - b.s)) <= 0)
        return std::abs((b.t - b.s) ^ (a - b.s)) / (b.t - b.s).len();
    return std::min((a - b.s).len(), (a - b.t).len());
}

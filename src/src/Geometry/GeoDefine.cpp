#define cp const point &
#define cl const line &
#define cc const circle &
#define vp std::vector<point>
#define cvp const std::vector<point> &
#define ld long double // 可以自己改
#define db long double
std::mt19937 rnd(time(0));
const db eps = 1e-12;
const db pi = std::numbers::pi;
const db INF = 1e9;
int sgn(ld x) {
    return x > eps ? 1 : (x < -eps ? -1 : 0);
}
// ==================== atan2 ====================
// std::atan2(y, x)
// 返回向量 (x, y) 相对 x 轴正方向的有向极角。
// 注意参数顺序是 atan2(y, x)，不是 atan2(x, y)！

// 返回范围通常为 [-pi, pi]（边界细节涉及 ±0）。
// x == 0 时仍能正常使用

// ==================== acos ====================
// std::acos(x)
// 计算 arccos(x)。
// 定义域：x in [-1, 1]
// 返回范围：[0, pi]
// const long double PI = std::acos(-1.0L);

// 浮点误差可能使 cos_theta 略超 [-1, 1]，必须 clamp：
// cos_theta = std::clamp(cos_theta, -1.0L, 1.0L);
// theta = std::acos(cos_theta);

// std::clamp：
// if (x < l) return l;
// if (x > r) return r;
// return x;

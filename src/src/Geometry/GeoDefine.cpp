// 常用类型简写；使用前需先声明 point、line、circle。
#define cp const point &              // 只读点引用
#define cl const line &               // 只读直线引用
#define cc const circle &             // 只读圆引用
#define vp std::vector<point>         // 点集
#define cvp const std::vector<point> & // 只读点集引用
#define ld long double                // 坐标与几何计算类型，可按题目修改
#define db long double                // 普通浮点类型

std::mt19937 rnd(time(0));            // 随机化算法使用的随机数引擎
const db eps = 1e-12;                 // 绝对误差；坐标很大或很小时需调整
const db pi = std::numbers::pi;       // C++20
const db INF = 1e9;                   // 有限哨兵值，不是数值无穷大

int sgn(ld x) { // 带 eps 的三态符号：正数 1，负数 -1，近零 0
    return x > eps ? 1 : (x < -eps ? -1 : 0);
}
// ==================== atan2 ====================
// std::atan2(y, x)
// 返回向量 (x, y) 相对 x 轴正方向的有向极角。
// 注意参数顺序是 atan2(y, x)，不是 atan2(x, y)！
// 返回范围通常为 [-pi, pi]（边界细节涉及 ±0）。
// x == 0 时仍能正常使用；(0, 0) 的方向没有几何意义。

// ==================== acos ====================
// std::acos(x)
// 计算 arccos(x)。
// 定义域：x in [-1, 1]
// 返回范围：[0, pi]
// const long double PI = std::acos(-1.0L);
// 浮点误差可能使 cos_theta 略超 [-1, 1]，必须 clamp：
// cos_theta = std::clamp(cos_theta, -1.0L, 1.0L);
// theta = std::acos(cos_theta);
// std::clamp(x, l, r)：把 x 限制在闭区间 [l, r]。
// if (x < l) return l;
// if (x > r) return r;
// return x;

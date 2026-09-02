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
    return x > eps ? 1 : (x < eps ? -1 : 0);
}
// how to use: fabsl, sqrtl, acosl ...
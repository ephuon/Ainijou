struct point {
    ld x, y;
    
    point() = default; // 默认构造，会默认构造x和y
    point(ld _x, ld _y): x(_x), y(_y) {}

    point rot(ld t) const { // 绕原点逆时针旋转 t 弧度
        ld c = std::cos(t), s = std::sin(t);
        return point(x * c - y * s, x * s + y * c);
    }
    point rot90() const { return point(-y, x); }  // 逆时针旋转 90 度
    point _rot90() const { return point(y, -x); } // 顺时针旋转 90 度
    ld len() const { return std::sqrt(x * x + y * y); } // 向量长度
    ld len2() const { return x * x + y * y; } // 长度平方
    point unit() const { // 同方向单位向量；要求当前向量非零
        ld d = len();
        return point(x/d, y/d);
    }
    void read() {
        std::cin >> x >> y;
    }
    void show() const {
        std::cout << x << " " << y << "\n";
    }
};

bool operator < (cp a, cp b) { // 精确字典序 (x, y) 不使用 eps
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}
bool operator > (cp a, cp b) { // 精确字典序 (x, y) 不使用 eps
    return a.x == b.x ? a.y > b.y : a.x > b.x;
}
bool operator == (cp a, cp b) { // eps 意义下两坐标分别相等
    return !sgn(a.x-b.x) && !sgn(a.y-b.y);
}
point operator +(cp a, cp b) { // 向量加法
    return point(a.x+b.x, a.y+b.y);
}
point operator -(cp a, cp b) { // 向量减法
    return point(a.x-b.x, a.y-b.y);
}
point operator *(const ld &a, cp b) { // 标量乘向量；标量必须写在左侧
    return point(a * b.x, a * b.y);
}
point operator /(cp b, const ld &a) { // 向量除以标量；要求 a != 0
    return point(b.x/a, b.y/a);
}
ld operator *(cp a, cp b) { // 点积：|a||b|cos(theta)
    return a.x * b.x + a.y * b.y;
}
ld operator ^(cp a, cp b) { // 二维叉积：> 0 表示 b 在 a 的逆时针方向
    return a.x * b.y - a.y * b.x;
}
ld rad(cp a, cp b) { // 无向小夹角 [0, pi]；任一向量为零时约定返回 0
    if ((a.x == 0 && a.y == 0) || (b.x == 0 && b.y == 0)) return 0;
    return std::acos(std::clamp(a * b / a.len() / b.len(), -1.0L, 1.0L));
}
bool turn_left(cp a, cp b) { // 从向量 a 严格左转到 b；共线时返回 false
    return sgn(a ^ b) > 0;
}

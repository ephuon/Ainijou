struct point {
    ld x, y;
    
    point(const ld &x = 0, const ld &y = 0): x(x), y(y) {}
    point(cp a): x(a.x), y(a.y) {}

    point operator = (cp a) {
        x = a.x, y = a.y;
        return *this;
    }
    point rot(ld t) const { // 逆时针
        ld c = std::cos(t), s = std::sin(t);
        return point(x * c - y * s, x * s + y * c);
    }
    point rot90() const { return point(-y, x); } // 逆时针
    point _rot90() const { return point(y, -x); } // 顺时针
    ld len() const { return std::sqrtl(x * x + y * y); }
    ld len2() const { return x * x + y * y; }
    point unit() const { // 取单位向量
        ld d = len();
        return point(x/d, y/d);
    }
};

bool operator < (cp a, cp b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}
bool operator > (cp a, cp b) {
    return a.x == b.x ? a.y > b.y : a.x > b.x;
}
bool operator == (cp a, cp b) {
    return !sgn(a.x-b.x) && !sgn(a.y-b.y);
}
point operator +(cp a, cp b) {
    return point(a.x+b.x, a.y+b.y);
}
point operator -(cp a, cp b) {
    return point(a.x-b.x, a.y-b.y);
}
point operator *(const ld &a, cp b) {
    return point(a * b.x, a * b.y);
}
point operator /(cp b, const ld &a) {
    return point(b.x/a, b.y/a);
}
ld operator *(cp a, cp b) { // 点积
    return a.x * b.x + a.y * b.y;
}
ld operator ^(cp a, cp b) { // 叉积
    return a.x * b.y - a.y * b.x;
}
ld rad(cp a, cp b) { // 夹角 如果 a 或 b 为零向量则返回 0
    return std::acosl((a.x == 0 && a.y == 0 || b.x == 0 && b.y == 0) ? 0 : 
            (a * b / a.len() / b.len()));
}

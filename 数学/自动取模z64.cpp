// 自动取模
// mod 需为质数（逆元使用费马小定理）
struct z64 {
    i64 x;// 存储的值

    z64(i64 x = 0) : x((x %mod + mod) % mod) {}// 构造，处理负数
    explicit operator i64() const { return x; }// 转 i64（显式）

    z64 pow(i64 e) const {// 快速幂
        z64 res(1), base(*this);
        while (e) {
            if (e & 1) res *= base;
            base *= base;
            e >>= 1;
        }
        return res;
    }

    z64 inv() const { return pow(mod - 2); }// 逆元（mod 需为质数）

    z64 operator-() const { return z64(-x); }// 取负

    z64 &operator+=(const z64 &rhs) {// 加等
        if ((x += rhs.x) >= mod) x -= mod;
        return *this;
    }
    z64 &operator-=(const z64 &rhs) {// 减等
        if ((x -= rhs.x) < 0) x += mod;
        return *this;
    }
    z64 &operator*=(const z64 &rhs) {// 乘等（直接乘，mod < 2^31 时安全）
        x = x * rhs.x % mod;
        return *this;
    }
    z64 &operator/=(const z64 &rhs) { return *this *= rhs.inv(); }// 除等

    z64 &operator++() { return *this += 1; }// 前置++
    z64 &operator--() { return *this -= 1; }// 前置--
    z64 operator++(int) { z64 tmp(*this); ++*this; return tmp; }// 后置++
    z64 operator--(int) { z64 tmp(*this); --*this; return tmp; }// 后置--

    friend z64 operator+(z64 lhs, const z64 &rhs) { return lhs += rhs; }
    friend z64 operator+(z64 lhs, i64 rhs) { return lhs += z64(rhs); }
    friend z64 operator+(i64 lhs, z64 rhs) { return z64(lhs) += rhs; }
    friend z64 operator-(z64 lhs, const z64 &rhs) { return lhs -= rhs; }
    friend z64 operator-(z64 lhs, i64 rhs) { return lhs -= z64(rhs); }
    friend z64 operator-(i64 lhs, z64 rhs) { return z64(lhs) -= rhs; }
    friend z64 operator*(z64 lhs, const z64 &rhs) { return lhs *= rhs; }
    friend z64 operator*(z64 lhs, i64 rhs) { return lhs *= z64(rhs); }
    friend z64 operator*(i64 lhs, z64 rhs) { return z64(lhs) *= rhs; }
    friend z64 operator/(z64 lhs, const z64 &rhs) { return lhs /= rhs; }
    friend z64 operator/(z64 lhs, i64 rhs) { return lhs /= z64(rhs); }
    friend z64 operator/(i64 lhs, z64 rhs) { return z64(lhs) /= rhs; }

    friend bool operator==(const z64 &lhs, const z64 &rhs) { return lhs.x == rhs.x; }
    friend bool operator!=(const z64 &lhs, const z64 &rhs) { return lhs.x != rhs.x; }
    friend bool operator<(const z64 &lhs, const z64 &rhs) { return lhs.x < rhs.x; }
    friend bool operator>(const z64 &lhs, const z64 &rhs) { return lhs.x > rhs.x; }

    friend ostream &operator<<(ostream &os, const z64 &m) { return os << m.x; }
    friend istream &operator>>(istream &is, z64 &m) {
        i64 v;
        is >> v;
        m = z64(v);
        return is;
    }
};

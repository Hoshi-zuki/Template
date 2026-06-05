
// XOR shift
static u64 shift(u64 x, u64 mask) {
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= mask;
    return x;
}

// get random
static i64 random(i64 a, i64 b) {
    i64 x = shift((u64)rand(), (u64)rand());
    return  (x % (i64)(b - a + 1) + (b - a + 1)) % (b - a + 1) + a;
}


mt19937_64 rg(random_device{}());//随机数生成器
template<typename T>
T random(T _L, T _R) {//获得闭区间 [L,R] 的随机数
    return rg() % (_R - _L + 1) + _L;
}
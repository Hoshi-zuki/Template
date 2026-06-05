

i64 POW(i64 x, i64 b) {// 计算x^b   O(logb)
    i64 res = 1;
    while (b) {
        if (b & 1)res = res * x % mod;
        x = x * x % mod;
        b /= 2;
    }
    return res;
}
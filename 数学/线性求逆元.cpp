// 线性求逆元
struct INV {
    int n;// 最大值
    vector<i64>inv;

    INV(int _n) {// 设定预处理的最大值
        init(_n);
    }

    void init(int _n) {// 设定预处理的最大值
        n = _n;
        inv = vector<i64>(n + 1);
        inv[1] = 1;
        for (int i = 2; i <= n; ++i) {
            inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        }
    }

    const i64 &operator[](int _i) { // INV[i] 调用即可 
        assert(_i >= 1 && _i <= n);
        return inv[_i];
    }
};
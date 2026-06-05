
struct Comb {//阶乘逆元，组合数

    int n;//预处理的最大值
    vector<i64>f, g;//f为阶乘，g为对应逆元

    Comb(int _n) {//传入预处理的最大值
        init(_n);
    }

    void init(int _n) {//传入预处理的最大值
        n = _n;
        f = g = vector<i64>(n + 1);
        f[0] = 1;
        for (int i = 1;i <= n;++i) {
            f[i] = i * f[i - 1] % mod;
        }
        g[n] = POW(f[n], mod - 2);
        for (int i = n - 1;i >= 0;--i) {
            g[i] = g[i + 1] * (i + 1) % mod;
        }
    }

    i64 POW(i64 x, i64 b) {// 计算x^b   O(logb)
        i64 res = 1;
        while (b) {
            if (b & 1)res = res * x % mod;
            x = x * x % mod;
            b /= 2;
        }
        return res;
    }

    i64 C(int n, int k) {//获得组合数 C_{n}  ^{k}
        if (n < k || k < 0)return 0;
        return (f[n] * g[k] % mod) * g[n - k] % mod;
    }

    i64 A(int n, int k) {//获得排列数 A_{n}  ^{k}
        if (n < k || k < 0)return 0;
        return (f[n] * g[n - k]) % mod;
    }

};

//索引必须从0开始
struct Z {//扩展 KMP ， Z函数 z[i]表示从i开始的子串，与从0开始的子串的最长相同长度

    string s;//字符串
    int n;//字符串长度
    vector<int>data;// z函数 z[i]=data[i]

    Z(string _s) {//传入 字符串 原串 索引必须从0开始
        init(_s);
    }

    Z() { // 默认，后续需手动调用init
        n = 0;
    }

    void init(string _s) {//初始化，初始化Z函数，索引必须从0开始
        s = _s;
        n = s.length();
        data = vector<int>(n);
        data[0] = n;
        for (int i = 1, c = 1, r = 1, len = 0;i < n;++i) {
            len = i < r ? min(data[i - c], r - i) : 0;
            while (i + len < n && s[i + len] == s[len])len++;
            data[i] = len;
            if (len + i > r) {
                r = len + i;
                c = i;
            }
        }
    }

    const int &operator[](int _i) { // Z[i] 调用即可 
        assert(_i >= 0 && _i < n);
        return data[_i];
    }
};



//应配合 Z函数 使用
//索引必须从0开始   
struct E { // e 函数，e[i] 表示 t[ i ~ n ] 与 s 的 最长公共前缀 的长度

    string t;int n;// 后缀 串
    vector<int>data;// 后缀串的e函数
    Z z; // 匹配串的z函数

    E(string _s, string _t) {
        init(_s, _t);
    }

    void init(string _s, string _t) {
        t = _t;
        n = t.length();
        data = vector<int>(n);
        z.init(_s);
        for (int i = 0, c = 0, r = 0, len = 0;i < n;++i) {
            len = i < r ? min(z[i - c], r - i) : 0;
            while (i + len < n && len < z.n && t[i + len] == _s[len])len++;
            if (i + len > r) {
                r = i + len;
                c = i;
            }
            data[i] = len;
        }
    }

    const int &operator[](int _i) { // E[i] 调用即可 
        assert(_i >= 0 && _i < n);
        return data[_i];
    }

};
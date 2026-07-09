
struct KMP {
    int n;
    string s;// 0-index
    vector<int>nxt;// nxt[i] 表示s_{ 0 ~ i-1 } 最长相同前后缀的长度 nxt[0] = -1

    KMP(string _s) {
        init(_s);
    }

    void init(string _s) {//初始化
        s = _s;
        n = _s.length();
        nxt = vector<int>(n + 1, 0);
        get_nxt();
    }

    vector<int>get_nxt() {// 获取 nxt
        if (nxt[0] == -1)return nxt;
        nxt[0] = -1;
        nxt[1] = 0;
        for (int i = 2;i <= n;++i) {
            int len = nxt[i - 1];
            while (len >= 0 && s[i - 1] != s[len]) {
                len = nxt[len];
            }
            nxt[i] = len + 1;
        }
        return nxt;
    }

    vector<int>work(string t) { // 找出 t 的所有子串中,是 s 的字符串的首索引
        int ind = 0;
        vector<int>res;
        for (int i = 0;i < t.length();++i) {
            while (ind > 0 && t[i] != s[ind]) {
                ind = nxt[ind];
            }
            if (t[i] == s[ind])ind++;
            if (ind == n) {
                res.push_back(i - ind + 1);
                ind = nxt[ind];
            }
        }
        return res;
    }
};
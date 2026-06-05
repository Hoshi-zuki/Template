
struct Manacher {//马拉车，求最长回文子串

    string s; //扩展串
    int n; //扩展串长度
    vector<int>p; //回文半径数组，p[i]表示扩展串中以i作为中心时的最长回文半径
    int mx;//最长回文子串的长度

    Manacher(string _s) { // 传入原串
        init(_s);
    }

    void init(string _s) { //初始化，Manacher
        s = "#";
        n = _s.length() * 2 + 1;
        for (auto &x : _s) {
            s.push_back(x);
            s.push_back('#');
        }
        p = vector<int>(n);
        mx = 0;
        for (int i = 0, r = 0, c = 0, len = 0;i < n;++i) {
            len = i < r ? min(p[2 * c - i], r - i) : 1;
            while (i + len < n && i - len >= 0 && s[i + len] == s[i - len])len++;
            if (i + len > r) {
                r = i + len;
                c = i;
            }
            p[i] = len;
            mx = max(mx, len - 1);
        }
    }

    int getans() { //获得最长回文子串长度
        return mx;
    }

};
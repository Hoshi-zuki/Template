// 后缀数组，0-index   (基数排序+倍增)  O(n log n)
struct SA {

    int n;// 字符串长度
    vector<int>sa;// sa[i] 从小到大 排名为 i 的后缀的初始索引（0-index）
    vector<int>rk;// rk[i] 后缀[i ... n-1] 的排名

    int k;// 当前比较的长度
    vector<int>tmp;// 用于更新rk
    vector<int>cnt;// 用于排序
    vector<int>old;// 用于排序

    vector<int>height;// height数组，height[i]为排名为i的后缀和排名为i-1的后缀的LCP（最长公共前缀）
    // 即  height[i]= LCP(sa[i],sa[i-1]);
    // 引理1：LCP(sa[i],sa[j])= \min height[ i+1, ... ,j ]
    // 引理2：字符串不同子串个数为：n(n+1)/2 - \sum height

    SA(const string &s) {//传入原始字符串
        init(s);
    }

    void init(const string &s) {//传入原始字符串
        n = s.length(), k = 1;
        tmp = cnt = old = sa = rk = vector<int>(n, 0);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](auto x, auto y) {return s[x] < s[y];});// 初始排序
        for (int i = 1;i < n;++i) {
            rk[sa[i]] = rk[sa[i - 1]];
            if (s[sa[i]] != s[sa[i - 1]])rk[sa[i]]++;
        }
        while (k < n) {
            _sort();
            tmp[sa[0]] = 0;
            for (int i = 1;i < n;++i) {
                tmp[sa[i]] = tmp[sa[i - 1]];
                if (rk[sa[i]] != rk[sa[i - 1]] || rk2(sa[i]) != rk2(sa[i - 1]))tmp[sa[i]]++;
            }
            for (int i = 0;i < n;++i) {
                rk[i] = tmp[i];
                if (rk[i] == n - 1)k = n;
            }
            k <<= 1;
        }
        // 以下为 构建 height 数组的过程：O(n)
        height = vector<int>(n, 0);
        for (int i = 0, len = 0;i < n;++i) {
            if (rk[i] == 0)continue;
            if (len)--len;
            while (s[i + len] == s[sa[rk[i] - 1] + len])++len;//末尾'\0'，故不存在越界 
            height[rk[i]] = len;
        }
    }

    int rk2(int i) {// 获得当前第二关键字
        if (i + k < n)return rk[i + k];
        return -1;
    }

    void _sort() {// 将sa数组按当前(rk,rk2)排序
        // 按 rk2 排     由于特性，不需要桶
        int cur = 0;
        for (int i = n - k;i < n;++i)old[cur++] = i;
        for (int i = 0;i < n;++i)if (sa[i] >= k)old[cur++] = sa[i] - k;

        // 按 rk  排     
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0;i < n;++i)cnt[rk[old[i]]]++;
        for (int i = 1;i < n;++i)cnt[i] += cnt[i - 1];
        for (int i = n - 1;i >= 0;--i)sa[--cnt[rk[old[i]]]] = old[i];
    }

    const int &operator[](int _i) { // SA[i]=SA.sa[i];
        assert(_i >= 0 && _i < n);
        return sa[_i];
    }
};

//给定若干个字符串的height数组，如何求两两LCP之和？
//对于这若干个字符串是一个字符串的所有后缀的情况：
//先给后缀排序，然后任意两个的LCP=min(height[i+1,......., j])，
//那么对于每个后缀而言，比其小的后缀（从自己开始向左走）提供的LCP一定不会增加，向右也是一个道理。
//于是做法是单调栈扫height，正着一遍，倒着一遍去统计。
//把sa.height放入该函数，返回值就是所有后缀两两LCP之和（每一有序对算了两次）
i64 get(const vector<int> &vec) {
    int n = vec.size();
    i64 res = 0;
    i64 now = 0;
    vector<array<int, 2>>stk;
    for (int i = 1;i < n;++i) {
        int num = 1;
        while (stk.size() && vec[i] <= vec[stk.back()[0]]) {
            now -= (i64)vec[stk.back()[0]] * stk.back()[1];
            num += stk.back()[1];
            stk.pop_back();
        }
        now += (i64)vec[i] * num;
        res += now;
        stk.push_back({ i,num });
    }
    stk.resize(0);
    now = 0;
    for (int i = n - 1;i >= 1;--i) {
        int num = 1;
        while (stk.size() && vec[i] <= vec[stk.back()[0]]) {
            now -= (i64)vec[stk.back()[0]] * stk.back()[1];
            num += stk.back()[1];
            stk.pop_back();
        }
        now += (i64)vec[i] * num;
        res += now;
        stk.push_back({ i,num });
    }
    return res;
}

//如果只是给定其中几个后缀，求两两LCP之和
//那么像虚树那样，把这几个后缀的rk拿出来排序，再用st表求每一个和前一个的LCP，组成新height数组
//然后再丢给上面的函数就行了！
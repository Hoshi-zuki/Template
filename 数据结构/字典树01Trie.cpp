
template<typename T>
struct Trie {//字典树  01 Trie

    int N; //总空间
    int B; //位宽
    vector<array<int, 2>>nxt; //儿子索引
    vector<int>pre; //相同前缀数量
    vector<int>cnt; //该字符串数量
    int rt = 1;//根节点
    int cur = 1;//内存已分配数量，下一个分配的内存索引为cur+1

    Trie(int _N, int _B) {  //传入预估数字数量 和 数字的bit数  空间复杂度 O(n*B)
        init(_N, _B);
    }

    void init(int _n, int _B) {  //传入预估数字数量 和 数字的bit数  空间复杂度 O(n*B)
        N = _n * _B + 7;
        B = _B;
        cnt = pre = vector<int>(N);
        nxt = vector<array<int, 2>>(N);
        cur = rt = 1;
    }

    void clear() {  //不改变空间，仅改变内存指针，原先旧数据在新开点时清空
        rt = cur = 1;
        pre[rt] = cnt[rt] = 0;
        nxt[rt].fill(0);
    }

    string trans(T val) {  //转成01字符串
        string res;
        for (int i = B - 1;i >= 0;--i) {
            if (val >> i & 1)res += "1";
            else res += "0";
        }
        return res;
    }

    void insert(T val, int num = 1) {  //插入一个数num次
        string str = trans(val);
        int pos = rt;
        pre[pos] += num;
        for (auto &x : str) {
            if (!nxt[pos][x - '0']) {
                nxt[pos][x - '0'] = ++cur;
                nxt[cur].fill(0);pre[cur] = cnt[cur] = 0;//如果clear ，先清除原先脏数据
            }
            pos = nxt[pos][x - '0'];
            pre[pos] += num;
        }
        cnt[pos] += num;
    }

    int find(T val) {  //找到某数字准确位置的内存编号
        string str = trans(val);
        int pos = rt;
        for (auto &x : str) {
            if (!nxt[pos][x - '0'])return 0;
            pos = nxt[pos][x - '0'];
        }
        return pos;
    }

    int findkmax(int k) {//找到第k大   返回-1指不存在
        int pos = rt;
        if (k <= 0 || pre[rt] < k)return -1;
        T ans = 0;
        for (int i = B - 1;i >= 0;--i) {
            if (pre[nxt[pos][1]] >= k) {
                pos = nxt[pos][1];
                ans |= 1 << i;
            } else {
                k -= pre[nxt[pos][1]];
                pos = nxt[pos][0];
            }
        }
        return ans;
    }

    int findkmin(int k) {//找到第k小   返回-1指不存在
        int pos = rt;
        if (k <= 0 || pre[rt] < k)return -1;
        T ans = 0;
        for (int i = B - 1;i >= 0;--i) {
            if (pre[nxt[pos][0]] >= k) {
                pos = nxt[pos][0];
            } else {
                k -= pre[nxt[pos][0]];
                pos = nxt[pos][1];
                ans |= 1 << i;
            }
        }
        return ans;
    }

    int queryltnum(T val) {//查询严格小于val的数的数量
        int res = 0;
        string str = trans(val);
        int pos = rt;
        for (auto &x : str) {
            if (x == '1') {
                res += pre[nxt[pos][0]];
            }
            if (!nxt[pos][x - '0'])break;
            pos = nxt[pos][x - '0'];
        }
        return res;
    }

    int querygtnum(T val) {//查询严格大于val的数的数量
        int res = 0;
        string str = trans(val);
        int pos = rt;
        for (auto &x : str) {
            if (x == '0') {
                res += pre[nxt[pos][1]];
            }
            if (!nxt[pos][x - '0'])break;
            pos = nxt[pos][x - '0'];
        }
        return res;
    }

    T findsuf(T val) {//找到后继，即第一个大于val的数   返回-1指不存在
        int k = querygtnum(val);
        return findkmax(k);
    }

    T findpre(T val) {//找到前驱，即第一个小于val的数   返回-1指不存在
        int k = queryltnum(val);
        return findkmin(k);
    }

};
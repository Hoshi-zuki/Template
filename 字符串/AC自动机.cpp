// 简单ACAM，只能记录每个子串出现的次数。
// 如果需要获取某些子串出现的位置，必看下文！
// 首先给这些子串去重，然后
// 对于相同长度的不同子串，出现的位置一定不同，于是同一长度的所有子串出现的位置最多有n个。
// 所以所有子串总出现的位置最多有 n * sqrt(|T|) 个，其中 |T| 是所有子串的长度和。
// 再看如何快速获取这些位置：
// 在读文本串时，每read到一个节点，你需要
// 从该节点开始沿着fail指针，向上走
// 给沿途的end[u]=1的节点（即某个模式串的末尾节点）push_back一下当前读到的索引（即标记）
// 这个索引就是该子串出现的在文本串中某次出现的 尾索引
// 这样暴力向上跳显然是不行的，而由于上述的根号限制，如果我们只访问end=1的节点，复杂度就能保证了
// 于是预处理一下，预处理 沿着fail向上跳的最近end=1的节点指针 ，存入up数组即可。
// 每次沿着 up 向上跳就行！
// up 和 存标记用的vector模板里面都没有，赛时自己添加并初始化
// 求up只需要在build()的while循环中添加以下内容
// if (end[fail[x]]) {
//     up[x] = fail[x];
// } else {
//     up[x] = up[fail[x]];
// }
//
// 然后在read()添加
// int x = now;
// while (x) {
//     if (end[x])tag[x].push_back(i);
//     x = up(x);
// }
// 其中 i 是当前读到的字符索引

struct ACAM {//AC自动机

    int N; //空间
    static constexpr int B = 26;
    vector<array<int, B>>nxt; //儿子索引
    vector<vector<int>>G; // fail反图
    vector<int>fail;//fail指针
    vector<int>times;//访问次数
    vector<int>Alert;//报警标识
    vector<int>end;// 标识是否是某个模式串的末尾节点
    //end[cur]如果是1说明cur节点是某个模式串的末尾节点！
    int rt;//根节点
    int cur;//内存已分配数量，下一个分配的内存索引为cur+1

    ACAM(int _N) {//传入预估结点数量
        init(_N);
    }

    void init(int _N) {//传入预估结点数量  即\sum |Str|
        N = _N + 7;
        nxt = vector<array<int, B>>(N);
        G = vector<vector<int>>(N);
        times = Alert = fail = vector<int>(N, 0);
        cur = rt = 0;
    }

    int trans(char x) {// 字符映射索引规则
        return x - 'a';
    }

    int insert(string str) {//插入字符串，插完别忘了build，返回该字符串末尾节点编号
        int pos = rt;
        for (auto &x : str) {
            auto i = trans(x);
            if (nxt[pos][i] == 0)nxt[pos][i] = ++cur;
            pos = nxt[pos][i];
        }
        Alert[pos] = 1;
        end[pos] = 1;
        return pos;
    }

    int find(string str) {//找到字符串尾位置的内存编号
        int pos = rt;
        for (auto &x : str) {
            if (!nxt[pos][trans(x)])return 0;
            pos = nxt[pos][trans(x)];
        }
        return pos;
    }

    void build() { //更新fail指针   insert完别忘了
        queue<int>Q;
        fail[0] = 0;
        for (int i = 0; i < B; i++) {
            if (nxt[0][i]) Q.push(nxt[0][i]);
        }
        while (Q.size()) {
            int x = Q.front();
            Q.pop();
            if (Alert[fail[x]])Alert[x] = 1;
            for (int i = 0;i < B;++i) {
                if (nxt[x][i] == 0)nxt[x][i] = nxt[fail[x]][i];
                else if (!fail[nxt[x][i]]) {
                    fail[nxt[x][i]] = nxt[fail[x]][i];
                    Q.push(nxt[x][i]);
                }
            }
        }
        for (int i = 1;i <= cur;++i) {
            G[fail[i]].push_back(i);
        }
    }

    void read(string s) {
        int now = 0;
        for (auto &x : s) {
            now = nxt[now][trans(x)];
            times[now]++;
        }
        dfs(0);
    }

    void dfs(int x) {
        for (auto &y : G[x]) {
            dfs(y);
            times[x] += times[y];
        }
    }

    int query(string s) { //  read完查询某字符串出现次数
        return times[find(s)];
    }

    bool alert(int x) {//判断结点x是否触发警报
        return Alert[x];
    }

};
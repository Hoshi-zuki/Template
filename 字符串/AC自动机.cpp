struct ACAM {//AC自动机

    int N; //空间
    static constexpr int B = 26;
    vector<array<int, B>>nxt; //儿子索引
    vector<vector<int>>G; // fail反图
    vector<int>fail;//fail指针
    vector<int>times;//访问次数
    vector<int>Alert;//报警
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

    void insert(string str) {//插入字符串，插完别忘了build
        int pos = rt;
        for (auto &x : str) {
            auto i = trans(x);
            if (nxt[pos][i] == 0)nxt[pos][i] = ++cur;
            pos = nxt[pos][i];
        }
        Alert[pos] = 1;
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
// 求强连通分量
struct SCC {
    int n;//图大小（1~n）
    vector<vector<int>>G;//原图
    vector<int>dfn, low, ins, sta, bel;
    int cur = 0;
    int scc = 0;

    SCC(int _n) {
        init(_n);
    }

    void init(int _n) {//初始化
        n = _n;
        G = vector<vector<int>>(n + 1);
        bel = dfn = low = ins = vector<int>(n + 1, 0);
    }

    void addEdge(int u, int v) {//加边
        G[u].push_back(v);
    }

    void tarjan(int x) {
        dfn[x] = low[x] = ++cur;
        ins[x] = 1;
        sta.push_back(x);
        for (auto &y : G[x]) {
            if (!dfn[y]) {
                tarjan(y);
                low[x] = min(low[x], low[y]);
            } else if (ins[y]) {
                low[x] = min(low[x], dfn[y]);
            }
        }
        if (low[x] == dfn[x]) {
            scc++;
            while (sta.size()) {
                auto now = sta.back();
                sta.pop_back();
                bel[now] = scc;
                ins[now] = 0;
                if (now == x)break;
            }
        }
    }

    void work() { // 缩点
        scc = 0;
        cur = 0;
        for (int i = 1;i <= n;++i) {
            if (!dfn[i]) {
                tarjan(i);
            }
        }
    }

    const int &operator[](int x) {//返回属于的SCC编号
        assert(scc > 0);
        assert(0 < x && x <= n);
        return bel[x];
    }
};
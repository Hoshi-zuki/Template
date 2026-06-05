struct LCA {//  O(1) 求LCA，欧拉序
    struct ST {
        int n;
        int B;
        vector<int>Lg;
        vector<vector<int>>st;
        void init(const vector<int> &_vec) {
            n = _vec.size();
            Lg = vector<int>(n + 1);
            for (int i = 1;i <= n;++i)Lg[i] = log2(i);
            B = Lg[n] + 1;
            st = vector<vector<int>>(n, vector<int>(B));
            for (int i = 0;i < n;++i)st[i][0] = _vec[i];
            for (int k = 1;k < B;++k) {
                for (int i = 0;i < n;++i) {
                    st[i][k] = min(st[i][k - 1], st[min(i + (1 << k - 1), n - 1)][k - 1]);
                }
            }
        }
        int query(int l, int r) {
            int k = Lg[r - l + 1];
            return min(st[l][k], st[r - (1 << k) + 1][k]);
        }
    };

    ST st;
    int n, rt;
    vector<vector<int>>G;
    vector<int>dfn, rk;
    bool finished;

    LCA(int _n, int _rt = 1) { //传入 图大小 和 根节点编号
        init(_n, _rt);
    }

    void init(int _n, int _rt = 1) {//传入 图大小 和 根节点编号
        n = _n;
        G = vector<vector<int>>(n + 1);
        finished = false;
        rt = _rt;
    }

    void addEdge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void build() {
        finished = true;
        const int N = 2 * n;
        dfn = vector<int>(N);
        int cur = 0;
        auto dfs = [&](auto self, int x, int fa) -> void {
            dfn[++cur] = x;
            for (auto &y : G[x]) {
                if (y == fa)continue;
                self(self, y, x);
                dfn[++cur] = x;
            }
        };
        dfs(dfs, rt, 0);
        rk = vector<int>(n + 1);
        for (int i = 1;i < N;++i) {
            if (!rk[dfn[i]])rk[dfn[i]] = i;
        }
        vector<int>tmp(N);
        for (int i = 1;i < N;++i) {
            tmp[i] = rk[dfn[i]];
        }
        st.init(tmp);
    }

    int query(int x, int y) {//查询 x 和 y 的 LCA
        if (!finished)build();
        return dfn[st.query(min(rk[x], rk[y]), max(rk[x], rk[y]))];
    }
};

struct DFZ {// 点分治

    int n;//图大小
    vector<vector<int>>G;//图
    vector<int>vis;//作为重心过的点
    vector<int>siz;//子树大小，求重心临时使用
    int rt;//当前分治子树的临时根

    DFZ(int _n) {
        init(_n);
    }

    void init(int _n) {//初始化
        n = _n;
        G = vector<vector<int>>(_n + 1);
        vis = vector<int>(_n + 1, 0);
        siz = vector<int>(_n + 1, 0);
    }

    void addEdge(int u, int v) {//添边
        G[u].push_back(v);
        G[v].push_back(u);
    };

    void get_siz(int x, int fa = 0) {//更新siz数组
        siz[x] = 1;
        for (auto &y : G[x]) {
            if (vis[y] || y == fa)continue;
            get_siz(y, x);
            siz[x] += siz[y];
        }
    }

    int get_centroid(int x, int fa = 0) {//找重心(从任意一点开始)
        for (auto &y : G[x]) {
            if (vis[y] || y == fa)continue;
            if (siz[y] >= siz[rt] / 2)return get_centroid(y, x);
        }
        return x;
    }

    i64 work(int x) {//点分治求解逻辑
        i64 res = 0;
        rt = x;
        get_siz(rt);
        int centroid = get_centroid(rt);


        //Main  计算主要逻辑


        //Main


        vis[centroid] = 1;
        for (auto &y : G[centroid]) {
            if (vis[y])continue;
            res += work(y);
        }
        return res;
    }
};
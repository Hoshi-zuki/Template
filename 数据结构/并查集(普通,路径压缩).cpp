
//基础并查集
struct DSU {
    int n;
    vector<int>fa;

    DSU(int _n) {//可维护集合0~_n
        init(_n);
    }

    void init(int _n) {
        n = _n + 1;
        fa = vector<int>(n);
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int x) {//找到头
        if (x == fa[x])return x;
        return fa[x] = find(fa[x]);
    }

    void merge(int x, int y) {//合并
        if (find(x) == find(y))return;
        fa[find(x)] = find(y);
    }

    bool same(int x, int y) {//是否在同一集合
        return find(x) == find(y);
    }
};


//基础并查集，包含查询集合大小
struct DSU {
    int n;
    vector<int>fa;
    vector<int>siz;

    DSU(int _n) {
        init(_n);
    }

    void init(int _n) {
        n = _n + 1;
        fa = vector<int>(n);
        iota(fa.begin(), fa.end(), 0);
        siz = vector<int>(n, 1);
    }

    int find(int x) {
        if (x == fa[x])return x;
        return fa[x] = find(fa[x]);
    }

    int get_size(int x) {
        return siz[find(x)];
    }

    void merge(int x, int y) {
        if (find(x) == find(y))return;
        siz[find(y)] = siz[find(y)] + siz[find(x)];
        fa[find(x)] = find(y);
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};
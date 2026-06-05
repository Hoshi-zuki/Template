
template<typename T>
struct DSU {
    int n;//集合数量+1
    vector<T>val;//权
    vector<int>fa;//父亲
    vector<int>siz;//所在集合大小，只有头结点有效

    DSU(int _n) { //传入需要维护集合数量
        init(_n);
    }

    void init(int _n) { //传入需要维护集合数量
        n = _n + 1;
        val = vector<T>(n);
        siz = fa = vector<int>(n);
        for (int i = 0;i < n;++i) {
            fa[i] = i;
            siz[i] = 1;
        }
    }

    int find(int x) { //找到x所在集合头，并路径压缩
        if (x == fa[x])return x;
        int y = fa[x];
        int res = find(y);
        val[x] = val[x] + val[y];
        return fa[x] = res;
    }

    bool merge(int u, int v, T w = 0) { // w = val[v] - val[u] ;
        int fu = find(u);
        int fv = find(v);
        if (fu == fv) {
            return 0; // merge失败，原本就在同一集合，需要额外判冲突
        }
        val[fu] = val[v] - val[u] - w;
        fa[fu] = fv;
        siz[fv] += siz[fu];
        return 1;
    }

    bool same(int u, int v) { //查询是否在同一集合
        return find(u) == find(v);
    }

    int size(int u) { //查询所在集合当前大小
        return siz[find(u)];
    }

    T query(int u, int v) { //询问前保证二者在同一集合,获得 val[v] - val[u]
        if (!same(u, v))return 0; //不应该触发
        return val[v] - val[u];
    }
};
//可撤销基础并查集，小挂大
struct DSU {
    int n;//可维护0~n
    vector<int>fa;//父亲
    vector<int>siz;//该集合点的数量，只有根结点有效
    vector<array<int, 3>>lst;//储存历史array=[fu,fv,siz[fv]],历史上进行的操作即fa[fu]=fv,siz[fv]+=siz[fu];
    DSU(int _n) {
        init(_n);
    }

    void init(int _n) {
        n = _n + 1;
        fa = vector<int>(n);
        iota(fa.begin(), fa.end(), 0);
        siz = vector<int>(n, 1);
    }

    int find(int x) {//找集合头
        if (x == fa[x])return x;
        return find(fa[x]);
    }

    int get_size(int x) {//获得集合大小
        return siz[find(x)];
    }

    bool merge(int x, int y) {//merge成功返回1，如果已经再同一集合返回0。不论是否成功都算可撤销的一次操作。
        int fu = find(x), fv = find(y);
        if (fu == fv) {
            lst.push_back({ -1,-1,-1 });
            return false;
        }
        if (siz[fu] > siz[fv])swap(fu, fv);
        lst.push_back({ fu,fv,siz[fv] });
        fa[fu] = fv;
        siz[fv] += siz[fu];
        return true;
    }

    bool roll_back() {//将上一次merge回退,如果已经没有可回退的操作，返回0，否则视为回退成功，返回1
        if (lst.size() == 0)return 0;
        if (lst.back()[0] == -1) {
            lst.pop_back();
            return 1;
        }
        auto &[fu, fv, siz_fv] = lst.back();
        siz[fv] = siz_fv;
        fa[fu] = fu;
        lst.pop_back();
        return 1;
    }

    bool same(int x, int y) {//判断是否在同一集合
        return find(x) == find(y);
    }

};
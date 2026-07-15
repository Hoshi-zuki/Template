
//线段树优化建图 (带权) 不带权的在底下
template<typename T>
struct SegEdge {

    int n;//编号最大值
    int N;//实际可使用的节点数
    int cur;
    vector<vector<pair<int, T>>>G;
    vector<int>ls, rs;//左右儿子
    vector<array<int, 2>>range;//维护范围
    int uprt;   //向上连边的树根
    int downrt; //向下连边的树根

    SegEdge(int _n, int _q) {//n为原始结点数量，q为预计区间->区间的边数量
        init(_n, _q);
    }

    void init(int _n, int _q) {// 初始化
        n = _n;
        N = n * 10 + _q;
        cur = n;
        G = vector<vector<pair<int, T>>>(N + 1);
        ls = rs = vector<int>(N + 1, 0);
        range = vector<array<int, 2>>(N + 1);
        uprt = build(1, n, 1);
        downrt = build(1, n);
    }

    int build(int l, int r, int type = 0) {// 建树,type=1则是向上连边
        if (l == r) {
            range[l] = { l,r };
            return l;
        }
        int mid = l + r >> 1;
        int rt = ++cur;
        ls[rt] = build(l, mid, type);
        rs[rt] = build(mid + 1, r, type);
        range[rt] = { l,r };
        if (type) {
            G[ls[rt]].push_back({ rt,0 });
            G[rs[rt]].push_back({ rt,0 });
        } else {
            G[rt].push_back({ ls[rt],0 });
            G[rt].push_back({ rs[rt],0 });
        }
        return rt;
    }

    void findNode(int l, int r, int ind, vector<int> &vec) {// 找ind这棵树被包含在[l,r]的节点，装入vec
        auto &[L, R] = range[ind];
        if (r<L || l>R)return;
        if (l <= L && R <= r) {
            vec.push_back(ind);
            return;
        }
        findNode(l, r, ls[ind], vec);
        findNode(l, r, rs[ind], vec);
    }

    void addEdge(int ul, int ur, int vl, int vr, T val) {//加边[ul,ur]->[vl,vr]
        vector<int>from, to;
        findNode(ul, ur, uprt, from);
        findNode(vl, vr, downrt, to);
        if (from.size() == 1) {
            auto &u = from[0];
            for (auto &v : to) {
                G[u].push_back({ v,val });
            }
            return;
        }
        if (to.size() == 1) {
            auto &v = to[0];
            for (auto &u : from) {
                G[u].push_back({ v,val });
            }
            return;
        }
        ++cur;//添加虚点
        for (auto &u : from) {
            G[u].push_back({ cur,0 });
        }
        for (auto &v : to) {
            G[cur].push_back({ v,val });
        }
    }

    const vector<pair<int, T>> &operator[](const int &ind) {
        return G[ind];
    }

};



//线段树优化建图 (不带权)
struct SegEdge {

    int n;//编号最大值
    int N;//实际可使用的节点数
    int cur;
    vector<vector<int>>G;
    vector<int>ls, rs;//左右儿子
    vector<array<int, 2>>range;//维护范围
    int uprt;   //向上连边的树根
    int downrt; //向下连边的树根

    SegEdge(int _n, int _q) {//n为原始结点数量，q为预计区间->区间的边数量
        init(_n, _q);
    }

    void init(int _n, int _q) {// 初始化
        n = _n;
        N = n * 10 + _q;
        cur = n;
        G = vector<vector<int>>(N + 1);
        ls = rs = vector<int>(N + 1, 0);
        range = vector<array<int, 2>>(N + 1);
        uprt = build(1, n, 1);
        downrt = build(1, n);
    }

    int build(int l, int r, int type = 0) {// 建树,type=1则是向上连边
        if (l == r) {
            range[l] = { l,r };
            return l;
        }
        int mid = l + r >> 1;
        int rt = ++cur;
        ls[rt] = build(l, mid, type);
        rs[rt] = build(mid + 1, r, type);
        range[rt] = { l,r };
        if (type) {
            G[ls[rt]].push_back(rt);
            G[rs[rt]].push_back(rt);
        } else {
            G[rt].push_back(ls[rt]);
            G[rt].push_back(rs[rt]);
        }
        return rt;
    }

    void findNode(int l, int r, int ind, vector<int> &vec) {// 找ind这棵树被包含在[l,r]的节点，装入vec
        auto &[L, R] = range[ind];
        if (r<L || l>R)return;
        if (l <= L && R <= r) {
            vec.push_back(ind);
            return;
        }
        findNode(l, r, ls[ind], vec);
        findNode(l, r, rs[ind], vec);
    }

    void addEdge(int ul, int ur, int vl, int vr) {//加边[ul,ur]->[vl,vr]
        vector<int>from, to;
        findNode(ul, ur, uprt, from);
        findNode(vl, vr, downrt, to);
        if (from.size() == 1) {
            auto &u = from[0];
            for (auto &v : to) {
                G[u].push_back(v);
            }
            return;
        }
        if (to.size() == 1) {
            auto &v = to[0];
            for (auto &u : from) {
                G[u].push_back(v);
            }
            return;
        }
        ++cur;//添加虚点
        for (auto &u : from) {
            G[u].push_back(cur);
        }
        for (auto &v : to) {
            G[cur].push_back(v);
        }
    }

    const vector<int> &operator[](const int &ind) {
        return G[ind];
    }

};
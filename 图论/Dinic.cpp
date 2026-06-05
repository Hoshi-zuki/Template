
template<typename T = i64>
struct Dinic {//Dinic求网络最大流

    struct edge {//边
        int to;
        T cap;
        int rev;
    };

    int n;
    const T INF = 1e18;// T 的正无穷取值
    vector<vector<edge>>G;//图
    vector<int>ind;//单向弧优化
    vector<int>level;//层数

    Dinic(int _n) {
        init(_n);
    }

    void init(int _n) {//初始化
        n = _n;
        G = vector<vector<edge>>(_n + 1);
        ind = vector<int>(_n + 1);
        level = vector<int>(_n + 1);
    }

    void addEdge(int u, int v, T cap) {//加边
        G[u].push_back({ v, cap, (int)G[v].size() });
        G[v].push_back({ u, 0, (int)G[u].size() - 1 });
    };

    bool bfs(int s, int t) {//bfs标层
        fill(level.begin(), level.end(), 0);
        queue<int>Q; Q.push(s); level[s] = 1;
        while (Q.size()) {
            int x = Q.front(); Q.pop();
            for (auto [to, cap, rev] : G[x]) {
                if (level[to] || cap <= 0)continue;
                level[to] = level[x] + 1;
                Q.push(to);
            }
        }
        if (level[t] > 0)return true;
        return false;
    };

    T dfs(int u, int t, T f) {//增广
        if (u == t)return f;
        for (auto &i = ind[u]; i < G[u].size();++i) {
            auto &e = G[u][i];
            if (e.cap > 0 && level[e.to] > level[u]) {
                T d = dfs(e.to, t, min(e.cap, f));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return T(0);
    };

    T work(int s, int t) {//求 s->t 网络最大流
        T maxflow = 0;
        while (bfs(s, t)) {
            fill(ind.begin(), ind.end(), 0);
            T f;
            while (f = dfs(s, t, INF)) {
                maxflow += f;
            }
        }
        return maxflow;
    }
};

//线段 y=kx+b 及id
struct Line {
    db k, b;
    int id;
};
//李超线段树
struct segment {
    const db eps = 1e-9;
    int n;//定义域区间 0 ~ n
    vector<Line>Node;//线段
    vector<int>L, R;//维护范围
    segment(int _n) {
        init(_n);
    }

    db cac(Line l, int x) {//求l在x处的取值
        return l.k * x + l.b;
    }

    int cmp(db a, db b) {//比较db的大小关系，返回 a-b 的正负 
        if (a - b > eps)return 1;
        if (b - a > eps)return -1;
        return 0;
    }

    pair<db, int>pmax(pair<db, int>a, pair<db, int>b) {//实现max pair<db,int>
        int flg = cmp(a.first, b.first);
        if (flg > 0)return a;
        if (flg < 0)return b;
        if (a.second < b.second)return a;
        return b;
    }

    void init(int _n) {
        n = _n;
        Node = vector<Line>(n + 1 << 2);
        L = R = vector<int>(n + 1 << 2);
        build(0, n, 1);
    }

    void build(int l, int r, int ind) {
        Node[ind] = { 0.0,0.0,0 };
        L[ind] = l, R[ind] = r;
        if (l == r)return;
        int mid = l + r >> 1;
        build(l, mid, ind << 1);
        build(mid + 1, r, ind << 1 | 1);
    }

    void upd(Line v, int ind) {//用线段v来更新该结点
        int mid = L[ind] + R[ind] >> 1;
        auto &u = Node[ind];
        int flg = cmp(cac(v, mid), cac(u, mid));
        if (flg > 0 || (flg == 0 && v.id < u.id)) {
            swap(u, v);
        }
        int fl = cmp(cac(v, L[ind]), cac(u, L[ind]));
        int fr = cmp(cac(v, R[ind]), cac(u, R[ind]));
        if (fl > 0 || (fl == 0 && v.id < Node[ind << 1].id))upd(v, ind << 1);
        if (fr > 0 || (fr == 0 && v.id < Node[ind << 1 | 1].id))upd(v, ind << 1 | 1);
    }

    void insert(int l, int r, Line val, int ind = 1) {//插入一条范围为[l,r]的线段
        if (L[ind] > r || R[ind] < l)return;
        if (l <= L[ind] && R[ind] <= r) {
            upd(val, ind);
            return;
        }
        insert(l, r, val, ind << 1);
        insert(l, r, val, ind << 1 | 1);
    }

    pair<db, int> query(int x, int ind = 1) {//查询x位置最高的线段编号，如果多个一样就是编号最小的
        if (L[ind] == R[ind])return { cac(Node[ind],x),Node[ind].id };
        int mid = L[ind] + R[ind] >> 1;
        db res = cac(Node[ind], x);
        if (x <= mid)return pmax(query(x, ind << 1), { res,Node[ind].id });
        return pmax(query(x, ind << 1 | 1), { res,Node[ind].id });
    }

};
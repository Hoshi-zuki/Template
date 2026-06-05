
// Segment 普通线段树  维护区间加，查询区间和/max/min
template<typename type>
struct SegTree {
    int n;
    struct T {
        int l, r;
        type sum, mx, mn, tag;
    };
    vector<T>Node;

    SegTree(int _n) {// 大小，维护的索引为 1 ~ n
        n = _n;
        Node = vector<T>(n << 2);
        build(1, n);
    }

    void build(int l, int r, int ind = 1) {
        int mid = l + r >> 1;
        Node[ind] = { l,r,0,0,0,0 };
        if (l == r)return;
        build(l, mid, ind << 1);
        build(mid + 1, r, ind << 1 | 1);
    }

    void up(int ind) {
        if (Node[ind].l == Node[ind].r)return;
        Node[ind].sum = Node[ind << 1].sum + Node[ind << 1 | 1].sum;
        Node[ind].mx = max(Node[ind << 1].mx, Node[ind << 1 | 1].mx);
        Node[ind].mn = min(Node[ind << 1].mn, Node[ind << 1 | 1].mn);
    }

    void down(int ind) {
        if (Node[ind].tag == 0)return;
        if (Node[ind].l != Node[ind].r) {
            auto &L = Node[ind << 1], &R = Node[ind << 1 | 1], &rt = Node[ind];
            L.sum += (L.r - L.l + 1) * rt.tag;
            R.sum += (R.r - R.l + 1) * rt.tag;
            L.mx += rt.tag;
            R.mx += rt.tag;
            L.mn += rt.tag;
            R.mn += rt.tag;
            L.tag += rt.tag;
            R.tag += rt.tag;
        }
        Node[ind].tag = 0;
    }

    void add(int jobl, int jobr, type val, int ind = 1) { //为jobl~jobr加上val
        auto &rt = Node[ind];
        if (jobr<rt.l || jobl>rt.r)return;
        else if (rt.l >= jobl && rt.r <= jobr) {
            rt.tag += val;
            rt.sum += (rt.r - rt.l + 1) * val;
            rt.mx += val;
            rt.mn += val;
            return;
        }
        down(ind);
        add(jobl, jobr, val, ind << 1);
        add(jobl, jobr, val, ind << 1 | 1);
        up(ind);
    }

    type querymin(int jobl, int jobr, int ind = 1) {//查询jibl~jobr最小值
        auto &rt = Node[ind];
        int mid = rt.r + rt.l >> 1;
        if (rt.l >= jobl && rt.r <= jobr) {
            return rt.mn;
        } else {
            down(ind);
            if (mid >= jobr) {
                return querymin(jobl, jobr, ind << 1);
            } else if (mid < jobl) {
                return querymin(jobl, jobr, ind << 1 | 1);
            } else {
                return min(querymin(jobl, jobr, ind << 1), querymin(jobl, jobr, ind << 1 | 1));
            }
        }
    }

    type querymax(int jobl, int jobr, int ind = 1) {//查询jibl~jobr最大值
        auto &rt = Node[ind];
        int mid = rt.r + rt.l >> 1;
        if (rt.l >= jobl && rt.r <= jobr) {
            return rt.mx;
        } else {
            down(ind);
            if (mid >= jobr) {
                return querymax(jobl, jobr, ind << 1);
            } else if (mid < jobl) {
                return querymax(jobl, jobr, ind << 1 | 1);
            } else {
                return max(querymax(jobl, jobr, ind << 1), querymax(jobl, jobr, ind << 1 | 1));
            }
        }
    }

    type querysum(int jobl, int jobr, int ind = 1) {//查询jibl~jobr的和
        auto &rt = Node[ind];
        int mid = rt.r + rt.l >> 1;
        if (rt.l >= jobl && rt.r <= jobr) {
            return rt.sum;
        } else {
            down(ind);
            if (mid >= jobr) {
                return querysum(jobl, jobr, ind << 1);
            } else if (mid < jobl) {
                return querysum(jobl, jobr, ind << 1 | 1);
            } else {
                return querysum(jobl, jobr, ind << 1) + querysum(jobl, jobr, ind << 1 | 1);
            }
        }
    }
};



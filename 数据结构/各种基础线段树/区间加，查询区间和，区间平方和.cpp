

// !!!!  现在的版本带取模，如果不取模请删除所有的%mod
// Segment 普通线段树  维护区间加，查询区间和,区间平方和
template<typename type>
struct SegTree {
    int n;
    struct T {
        int l, r;
        type sum, sum2, tag;
    };
    vector<T>Node;

    SegTree(int _n) {// 大小，维护的索引为 1 ~ n
        n = _n;
        Node = vector<T>(n << 2);
        build(1, n);
    }

    void build(int l, int r, int ind = 1) {
        int mid = l + r >> 1;
        Node[ind] = { l,r,0,0,0 };
        if (l == r)return;
        build(l, mid, ind << 1);
        build(mid + 1, r, ind << 1 | 1);
    }

    void up(int ind) {
        if (Node[ind].l == Node[ind].r)return;
        Node[ind].sum = (Node[ind << 1].sum + Node[ind << 1 | 1].sum) % mod;
        Node[ind].sum2 = (Node[ind << 1].sum2 + Node[ind << 1 | 1].sum2) % mod;
    }

    void down(int ind) {
        if (Node[ind].tag == 0)return;
        if (Node[ind].l != Node[ind].r) {
            auto &L = Node[ind << 1], &R = Node[ind << 1 | 1], &rt = Node[ind];
            add(L.l, L.r, rt.tag, ind << 1);
            add(R.l, R.r, rt.tag, ind << 1 | 1);
        }
        Node[ind].tag = 0;
    }

    void add(int jobl, int jobr, type val, int ind = 1) { //为jobl~jobr加上val
        auto &rt = Node[ind];
        if (jobr<rt.l || jobl>rt.r)return;
        else if (rt.l >= jobl && rt.r <= jobr) {
            rt.sum2 = (rt.sum2 + val * val % mod * (rt.r - rt.l + 1) % mod + 2 * val * rt.sum % mod) % mod;
            rt.tag += val;
            rt.sum += (rt.r - rt.l + 1) * val;
            rt.tag %= mod;
            rt.sum %= mod;
            return;
        }
        down(ind);
        add(jobl, jobr, val, ind << 1);
        add(jobl, jobr, val, ind << 1 | 1);
        up(ind);
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
                return (querysum(jobl, jobr, ind << 1) + querysum(jobl, jobr, ind << 1 | 1)) % mod;
            }
        }
    }

    type querysum2(int jobl, int jobr, int ind = 1) {//查询jibl~jobr的 平方 和 即\sum (a_i^2);
        auto &rt = Node[ind];
        int mid = rt.r + rt.l >> 1;
        if (rt.l >= jobl && rt.r <= jobr) {
            return rt.sum2;
        } else {
            down(ind);
            if (mid >= jobr) {
                return querysum2(jobl, jobr, ind << 1);
            } else if (mid < jobl) {
                return querysum2(jobl, jobr, ind << 1 | 1);
            } else {
                return (querysum2(jobl, jobr, ind << 1) + querysum2(jobl, jobr, ind << 1 | 1)) % mod;
            }
        }
    }
};
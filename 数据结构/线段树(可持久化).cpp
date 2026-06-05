

// 单点修改，区间查询 
template<typename type>
struct persistent_SegTree {
    int n; //下标 1~n
    int cnt;//分配结点
    int version;//当前最大版本号
    struct T {
        int l, r;        //维护的范围
        int left, right; //左右儿子的编号
        type sum, mx, mn;
    };

    vector<T>Node;
    vector<int>Root;//版本号为下标，值为根节点编号,   0为初始版本号

    persistent_SegTree(int _n, int max_version) {
        n = _n;
        cnt = 0;
        Root = vector<int>(max_version + 1);
        version = 0;
        int MAXN = n * 4 + max_version * ceil(log2(n) + 1);
        Node = vector<T>(MAXN);
        Root[0] = build(1, n);
    }

    int build(int L, int R) {
        int ind = ++cnt;
        auto &rt = Node[ind];
        rt.l = L, rt.r = R;
        rt.sum = rt.mx = rt.mn = 0;
        rt.left = rt.right = 0;
        if (L == R)return ind;
        int mid = L + R >> 1;
        rt.left = build(L, mid);
        rt.right = build(mid + 1, R);
        return ind;
    }

    int insert(int old_version, int index, type val) { // 默认是 set 为val ! ; 在int UPDATA()实现
        Root[++version] = UPDATA(Root[old_version], index, val);
        return version;
    }

    int UPDATA(int old_rt, int index, type val) {
        int ind = ++cnt;
        Node[ind] = Node[old_rt];
        auto &now = Node[ind];
        if (now.l == now.r) { // 更新逻辑
            now.mx = now.mn = now.sum = val;
            return ind;
        }
        int mid = now.l + now.r >> 1;
        if (index <= mid) {
            now.left = UPDATA(Node[old_rt].left, index, val);
        } else {
            now.right = UPDATA(Node[old_rt].right, index, val);
        }
        now.sum = (now.left > 0 ? Node[now.left].sum : 0) + (now.right > 0 ? Node[now.right].sum : 0);
        now.mx = max((now.left > 0 ? Node[now.left].mx : Node[now.right].mx), (now.right > 0 ? Node[now.right].mx : Node[now.left].mx));
        now.mn = min((now.left > 0 ? Node[now.left].mn : Node[now.right].mn), (now.right > 0 ? Node[now.right].mn : Node[now.left].mn));
        return ind;
    }

    type query_min(int jobl, int jobr, int Rt) {//查询jibl~jobr最小值, Rt=seg.Root[version]
        auto &rt = Node[Rt];
        int mid = rt.r + rt.l >> 1;
        if (rt.l >= jobl && rt.r <= jobr) {
            return rt.mn;
        } else {
            if (mid >= jobr) {
                return query_min(jobl, jobr, rt.left);
            } else if (mid < jobl) {
                return query_min(jobl, jobr, rt.right);
            } else {
                return min(query_min(jobl, jobr, rt.left), query_min(jobl, jobr, rt.right));
            }
        }
    }
    type query_max(int jobl, int jobr, int Rt) {//查询jibl~jobr最大值, Rt=seg.Root[version]
        auto &rt = Node[Rt];
        int mid = rt.r + rt.l >> 1;
        if (rt.l >= jobl && rt.r <= jobr) {
            return rt.mx;
        } else {
            if (mid >= jobr) {
                return query_max(jobl, jobr, rt.left);
            } else if (mid < jobl) {
                return query_max(jobl, jobr, rt.right);
            } else {
                return max(query_max(jobl, jobr, rt.left), query_max(jobl, jobr, rt.right));
            }
        }
    }
    type query_sum(int jobl, int jobr, int Rt) {//查询jibl~jobr的和, Rt=seg.Root[version]
        auto &rt = Node[Rt];
        int mid = rt.r + rt.l >> 1;
        if (rt.l >= jobl && rt.r <= jobr) {
            return rt.sum;
        } else {
            if (mid >= jobr) {
                return query_sum(jobl, jobr, rt.left);
            } else if (mid < jobl) {
                return query_sum(jobl, jobr, rt.right);
            } else {
                return query_sum(jobl, jobr, rt.left) + query_sum(jobl, jobr, rt.right);
            }
        }
    }

};
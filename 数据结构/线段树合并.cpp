

// 线段树合并  维护单点加，合并操作，查询区间sum，min，max
template<typename T>
struct SegTree {

    struct data {
        T sum;
        T mx;
        T mn;
        data() {//默认值
            sum = mx = mn = 0;
        }
        operator T()const {//将data转化成T
            return sum;
        }
        data &operator+=(const T &val) {//定义单点加
            sum += val;
            mx += val;
            mn += val;
            return *this;
        }
        data operator+(const data &x) {//定义 up合并
            data tmp = *this;
            tmp.sum += x.sum;
            tmp.mx = max(tmp.mx, x.mx);
            tmp.mn = min(tmp.mn, x.mn);
            return tmp;
        }
    };

    vector<array<int, 2>>range;//每个结点维护的范围
    vector<int>left, right;//左右儿子编号
    vector<data>val;//每个结点维护的信息
    int cur = 0;//分配结点编号
    int n;//维护闭区间 0~n
    int N;//总可用结点编号 1~N-1 

    int open(int l, int r) {
        ++cur;
        assert(cur < N);
        range[cur] = { l,r };
        return cur;
    }

    SegTree(int _n, int _m) {//维护区间为0 ~ n，预计add操作 m 次
        init(_n, _m);
    }

    void init(int _n, int _m) {//维护区间为0 ~ n，预计add操作 m 次
        N = _m * (__lg(_n + 1) + 2) + 7;
        n = _n;
        cur = 0;
        left = right = vector<int>(N, 0);
        val = vector<data>(N);
        range = vector<array<int, 2>>(N);
    }

    int build() {//开一个新线段树，默认全0，返回该线段树编号
        return open(0, n);
    }

    void up(int id) {//合并儿子信息
        auto &[l, r] = range[id];
        if (l == r)return;
        val[id] = val[left[id]] + val[right[id]];
    }

    void add(int id, int i, T w) {//对线段树 id 的 i 索引加上 w
        auto &[l, r] = range[id];
        if (l == r) {
            val[id] += w;
            return;
        }
        int mid = l + r >> 1;
        if (i <= mid) {
            if (left[id] == 0)left[id] = open(l, mid);
            add(left[id], i, w);
        } else {
            if (right[id] == 0)right[id] = open(mid + 1, r);
            add(right[id], i, w);
        }
        up(id);
    }

    int merge(int t1, int t2) {//合并t1，t2两颗线段树，返回新线段树根节点
        if (t1 == 0 || t2 == 0) {
            return t1 + t2;
        }
        auto &[l, r] = range[t1];
        if (l == r) {
            val[t1] += T(val[t2]);
        } else {
            left[t1] = merge(left[t1], left[t2]);
            right[t1] = merge(right[t1], right[t2]);
            up(t1);
        }
        return t1;
    }

    data query(int id, int l, int r) {//查询线段树id 的[l,r]范围的总信息
        if (id == 0) {
            return data();
        }
        auto &[cl, cr] = range[id];
        if (cl >= l && cr <= r)return val[id];
        int mid = cl + cr >> 1;
        if (r <= mid)return query(left[id], l, r);
        if (l > mid)return query(right[id], l, r);
        return query(left[id], l, r) + query(right[id], l, r);
    }

};
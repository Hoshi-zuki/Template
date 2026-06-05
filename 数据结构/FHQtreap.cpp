// FHQ Treap
mt19937_64 FHQ_rg(random_device{}());//随机数生成器
template<typename T = int>
struct FHQ {
    int n;//结点编号最大值
    vector<int>mem;//内存池
    vector<T>key;//结点信息
    vector<T>sum;//子数结点信息和
    vector<int>priority, siz;//结点权重，子树大小
    vector<int>left, right;//左右儿子编号
    int head = 0;//树头

    FHQ(int _n) {//传入预计传入结点的个数
        init(_n);
    }

    void init(int _n) {//初始化
        n = _n;
        head = 0;
        mem = vector<int>(n);
        for (int i = 0;i < n;++i)mem[i] = n - i;
        sum = key = vector<T>(n + 1);
        priority = siz = left = right = vector<int>(n + 1);
    }

    int open(T _key) {//开点
        assert(mem.size() > 0);
        int x = mem.back();
        mem.pop_back();
        priority[x] = FHQ_rg();
        sum[x] = key[x] = _key;
        siz[x] = 1;
        return x;
    }

    void clean(int x) {//回收内存，并清除
        left[x] = right[x] = 0;
        priority[x] = siz[x] = 0;
        sum[x] = key[x] = T(0);
        mem.push_back(x);
    }

    void clear(int x) {//回收 x 结点的整颗子树
        if (x == 0)return;
        clear(left[x]);
        clear(right[x]);
        clean(x);
    }

    void up(int x) {//整合子数信息
        siz[x] = siz[left[x]] + siz[right[x]] + 1;
        sum[x] = sum[left[x]] + sum[right[x]] + key[x];
    }

    //  ---------- 以下为分裂合并
    void split(int l, int r, int x, T num) {//按key分裂key<=num 。split后，left[0]为右侧树头，right[0]为左侧树头
        if (x == 0) {
            left[r] = right[l] = 0;
            return;
        }
        if (key[x] <= num) {
            right[l] = x;
            split(x, r, right[x], num);
        } else {
            left[r] = x;
            split(l, x, left[x], num);
        }
        up(x);
    }

    void split2(int l, int r, int x, int num) {//按rank分裂rank<=num（左子树有num个结点）
        if (x == 0) {
            left[r] = right[l] = 0;
            return;
        }
        if (siz[left[x]] + 1 <= num) {
            right[l] = x;
            split2(x, r, right[x], num - siz[left[x]] - 1);
        } else {
            left[r] = x;
            split2(l, x, left[x], num);
        }
    }

    int merge(int l, int r) {//合并，此操作钦定key[l]<=key[r]
        if (l == 0 || r == 0) {
            return l + r;
        }
        if (priority[l] > priority[r]) {
            right[l] = merge(right[l], r);
            up(l);
            return l;
        } else {
            left[r] = merge(l, left[r]);
            up(r);
            return r;
        }
    }

    //  ---------- 以下为功能函数 
    void add(T _key) {//加入一个数 key = _key
        split(0, 0, head, _key);
        head = open(_key);
        head = merge(merge(right[0], head), left[0]);
    }

    void del(T _key) { // 删除一个数 key = _key 
        split(0, 0, head, _key);
        int r = left[0];
        split(0, 0, right[0], _key - 1);
        int l = right[0], m = left[0];
        head = merge(merge(l, merge(left[m], right[m])), r);
        if (m > 0)clean(m);
    }

    int query_siz(T _key) { // 查询 key <= _key 的数量
        split(0, 0, head, _key);
        int res = siz[right[0]];
        head = merge(right[0], left[0]);
        return res;
    }

    int query_range_siz(T mn_key, T mx_key) { // 查询 mn_key <= key <= mx_key 的数量
        assert(mn_key <= mx_key);
        return query_siz(mx_key) - query_siz(mn_key - 1);
    }

    T query_sum(T _key) { // 查询 对于所有 key <= _key 的结点，key的和
        split(0, 0, head, _key);
        T res = sum[right[0]];
        head = merge(right[0], left[0]);
        return res;
    }

    T query_range_sum(T mn_key, T mx_key) { // 查询 对于所有 mn_key <= key <= mx_key 的结点，key的和
        assert(mn_key <= mx_key);
        return query_sum(mx_key) - query_sum(mn_key - 1);
    }

    T findkth(int num) {//查询 第 k 小
        split2(0, 0, head, num);
        int r = left[0];
        split2(0, 0, right[0], num - 1);
        int l = right[0];
        T res = key[left[0]];
        head = merge(merge(l, left[0]), r);
        return res;
    }
};
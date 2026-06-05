
// FHQ Treap   区间翻转 
mt19937_64 FHQ_rg(random_device{}());//随机数生成器
template<typename T = int>
struct FHQ {
    int n;//结点编号最大值
    vector<int>mem;//内存池
    vector<T>key;//结点信息
    vector<T>sum;//子数结点信息和
    vector<int>priority, siz;//结点权重，子树大小
    vector<int>left, right;//左右儿子编号
    vector<int>rev;//区间翻转懒标记
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
        rev = vector<int>(n + 1);
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

    void down(int x) {//下发懒标记
        if (rev[x]) {
            auto &l = left[x];
            auto &r = right[x];
            swap(l, r);
            if (l)rev[l] ^= 1;
            if (r)rev[r] ^= 1;
            rev[x] = 0;
        }
    }

    void up(int x) {//整合子数信息
        siz[x] = siz[left[x]] + siz[right[x]] + 1;
        sum[x] = sum[left[x]] + sum[right[x]] + key[x];
    }

    //  ---------- 以下为分裂合并
    void split(int l, int r, int x, int num) {//按rank分裂rank<=num（左子树有num个结点）
        if (x == 0) {
            left[r] = right[l] = 0;
            return;
        }
        down(x);
        if (siz[left[x]] + 1 <= num) {
            right[l] = x;
            split(x, r, right[x], num - siz[left[x]] - 1);
        } else {
            left[r] = x;
            split(l, x, left[x], num);
        }
        up(x);
    }

    int merge(int l, int r) {//合并，此操作钦定key[l]<=key[r]
        if (l == 0 || r == 0) {
            return l + r;
        }
        if (priority[l] > priority[r]) {
            down(l);
            right[l] = merge(right[l], r);
            up(l);
            return l;
        } else {
            down(r);
            left[r] = merge(l, left[r]);
            up(r);
            return r;
        }
    }

    //  ---------- 以下为功能函数 

    void insert(T _key, int rank) {//加入一个数 key = _key ,且其左侧共rank个数
        split(0, 0, head, rank);
        head = open(_key);
        head = merge(merge(right[0], head), left[0]);
    }

    void remove(int rank) {//删除 从小到大排名第 rank 个数
        assert(rank > 0);
        split(0, 0, head, rank);
        int r = left[0];
        split(0, 0, right[0], rank - 1);
        int l = right[0], m = left[0];
        head = merge(l, r);
        if (m > 0)clean(m);
    }

    void reverse(int l, int r) {//翻转区间[l,r]
        split(0, 0, head, r);
        int R = left[0];
        split(0, 0, right[0], l - 1);
        int M = left[0];
        int L = right[0];
        rev[M] ^= 1;
        head = merge(merge(L, M), R);
    }

    const T &operator[](int _rank) {//直接读取第_rank个数
        assert(_rank > 0 && _rank <= siz[head]);
        split(0, 0, head, _rank);
        int R = left[0];
        split(0, 0, right[0], _rank - 1);
        T &res = key[left[0]];
        head = merge(merge(right[0], left[0]), R);
        return res;
    }

};
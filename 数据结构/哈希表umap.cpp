
// 时间小常数，空间大常数   哈希表
template<typename _key, typename _value>
struct umap {

    using u32 = unsigned int;
    int N, cur;// 实际开的大小和已分配节点数
    vector<_key>data;//索引i存储占据该索引的kay
    vector<_value>va;//存储对应索引的value
    int exist_0;//是否存在 _key();

    umap(int n, int rate = 3) { init(n, rate); }

    void init(int n, int rate) {//表示开rate（一般3-7）倍空间，理论上越大速度越快
        N = n * rate + 7;
        exist_0 = cur = 0;
        data = vector<_key>(N, _key());
        va = vector<_value>(N, _value());
    }

    int count(_key key) { // 判断是否存在 key 的键值对
        if (key == _key())return exist_0;
        int start = u32(std::hash<_key>{}(key)) % u32(N - 1) + 1;
        while (1) {
            if (data[start] == _key())return 0;
            if (data[start] == key)return 1;
            if (++start == N)start = 1;
        }
    }

    _value &operator[](_key key) { // umap[key]访问元素，如果不存在则会自动创建！
        if (key == _key()) {
            if (!exist_0)exist_0 = 1, cur++;
            return va[0];
        }
        int start = u32(std::hash<_key>{}(key)) % u32(N - 1) + 1;
        assert(cur <= N - 7);
        while (1) {
            if (data[start] == _key())data[start] = key, cur++;
            if (data[start] == key)break;
            if (++start == N)start = 1;
        }
        return va[start];
    }

    int size() {
        return cur;
    }
};
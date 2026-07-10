

mt19937_64 rg(random_device{}());//随机数生成器
u64 b2 = rg() % int(1e9);
struct double_string_hash {// 0-index

    string s;
    vector<u64>Hash1, Hash2;
    vector<u64>pows1, pows2;
    u64 m2, b1;
    int n;

    double_string_hash(const string &s) {
        init(s);
    }
    double_string_hash() {}

    void init(const string &s) {
        b1 = 131;
        m2 = int(1e9) + 7;
        n = s.size();
        Hash1 = Hash2 = pows1 = pows2 = vector<u64>(n);
        Hash1[0] = Hash2[0] = s[0];
        pows1[0] = pows2[0] = 1;
        for (int i = 1;i < n;++i) {
            pows1[i] = pows1[i - 1] * b1;
            pows2[i] = pows2[i - 1] * b2 % m2;
            Hash1[i] = Hash1[i - 1] * b1 + s[i];
            Hash2[i] = (Hash2[i - 1] * b2 + s[i]) % m2;
        }
    }

    pair<u64, u64>ask(int l, int r) {// get [l,r] 的双哈希
        pair<u64, u64>res = { Hash1[r],Hash2[r] };
        if (l > 0) {
            res.first = res.first - Hash1[l - 1] * pows1[r - l + 1];
            res.second = res.second + m2 - Hash2[l - 1] * pows2[r - l + 1] % m2;
            res.second %= m2;
        }
        return res;
    }

};
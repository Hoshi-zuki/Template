

struct matrix_hash {// 0-index

    string s;
    vector<vector<u64>>Hash;
    vector<u64>powr, powc;
    u64 r, c;// 横，纵base
    int n, m;

    matrix_hash(const vector<string> &s) {
        init(s);
    }

    void init(const vector<string> &s) {
        r = 131;
        c = 10007;
        n = s.size();
        m = s[0].size();
        Hash = vector<vector<u64>>(n, vector<u64>(m, s[0][0]));
        powr = vector<u64>(m, 1);
        powc = vector<u64>(n, 1);
        for (int j = 1;j < m;++j) {
            powr[j] = powr[j - 1] * r;
            Hash[0][j] = Hash[0][j - 1] * r + s[0][j];
        }
        for (int i = 1;i < n;++i) {
            powc[i] = powc[i - 1] * c;
            Hash[i][0] = Hash[i - 1][0] * c + s[i][0];
        }
        for (int i = 1;i < n;++i) {
            for (int j = 1;j < m;++j) {
                Hash[i][j] = r * Hash[i][j - 1] + c * Hash[i - 1][j] - r * c * Hash[i - 1][j - 1] + s[i][j];
            }
        }
    }

    u64 ask(int i, int j, int I, int J) {// (i,j)~(I,J) 的哈希
        u64 res = Hash[I][J];
        if (i > 0)res -= Hash[i - 1][J] * powc[I - i + 1];
        if (j > 0)res -= Hash[I][j - 1] * powr[J - j + 1];
        if (i > 0 && j > 0)res += Hash[i - 1][j - 1] * powc[I - i + 1] * powr[J - j + 1];
        return res;
    }

};
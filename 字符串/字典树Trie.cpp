
struct Trie {//字典树

    int N; //空间
    vector<array<int, 26>>nxt; //儿子索引
    vector<int>pre; //相同前缀数量
    vector<int>cnt; //该字符串数量
    int rt = 1;//根节点
    int cur = 1;//内存已分配数量，下一个分配的内存索引为cur+1

    Trie(int _N) {////传入预估结点数量
        init(_N);
    }

    void init(int _N) {//传入预估结点数量  即\sum |Str|
        N = _N + 7;
        cnt = pre = vector<int>(N);
        nxt = vector<array<int, 26>>(N);
        cur = rt = 1;
    }

    void clear() {//不改变空间，仅改变内存指针，原先旧数据在新开点时清空
        rt = cur = 1;
        pre[rt] = cnt[rt] = 0;
        nxt[rt].fill(0);
    }

    int trans(char x) {// 字符映射索引规则
        return x - 'a';
    }

    void insert(string str) {//插入字符串
        int pos = rt;
        pre[pos]++;
        for (auto &x : str) {
            if (!nxt[pos][trans(x)]) {
                nxt[pos][trans(x)] = ++cur;
                nxt[cur].fill(0);pre[cur] = cnt[cur] = 0;//如果clear ，先清除原先脏数据
            }
            pos = nxt[pos][trans(x)];
            pre[pos]++;
        }
        cnt[pos]++;
    }

    int find(string str) {//找到字符串尾位置的内存编号
        int pos = rt;
        for (auto &x : str) {
            if (!nxt[pos][trans(x)])return 0;
            pos = nxt[pos][trans(x)];
        }
        return pos;
    }

    int querycnt(string str) {//查询某字符串插入的次数
        return cnt[find(str)];
    }

    int querypre(string str) {//查询某字符串作为前缀的次数
        return pre[find(str)];
    }

};
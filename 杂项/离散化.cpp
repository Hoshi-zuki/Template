
template<typename T>
struct DataSort {     // 1,2,3,...
    vector<T>ORG;  //获得原先的值
    vector<int>after; //离散化后的原数组
    map<T, int>M;
    int n;
    int maxind = 0;

    DataSort(vector<T> &in) { //nlogn
        init(in);
    }

    void init(vector<T> &in) { // nlogn
        n = in.size();
        after = vector<int>(n);
        vector<int>sorted = in;
        sort(sorted.begin(), sorted.end());
        for (auto &x : sorted) {
            if (!M.count(x)) {
                M[x] = ++maxind;
            }
        }
        ORG = vector<T>(maxind + 1);
        for (int i = 0;i < n;++i) {
            after[i] = M[in[i]];
            ORG[after[i]] = in[i];
        }
    }

    vector<int> getAfter() {//获得离散化后的数组
        return after;
    }

    vector<int> getORG() {//获得每个索引对应离散化前值的数组
        return ORG;
    }

    int get(T x) { //获得离散化后的值 O(logn)
        return M[x];
    }

    T org(int ind) {//获得离散化前的值 O(1)
        return ORG[ind];
    }

};
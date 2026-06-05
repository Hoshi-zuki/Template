
struct Prime { // prime - 埃氏筛  //

    vector<int>prime;     // 质数列表
    vector<int>isP;       // i是否是质数
    vector<int>minDivisor;// i的最小质因子
    int n;

    Prime(int maxnum) { //maxnum为值域最大值
        init(maxnum);
    }

    void init(int maxnum) {//maxnum为值域最大值
        n = maxnum;
        minDivisor = isP = vector<int>(n + 1, 1);
        for (int i = 0;i < 2 && i < n;++i) {
            isP[i] = 0;
            minDivisor[i] = i;
        }
        for (int i = 2;i <= n;++i) {
            if (isP[i]) {
                prime.push_back(i);
                minDivisor[i] = i;
                for (int j = 2 * i;j <= n;j += i) {
                    if (isP[j]) {
                        isP[j] = 0;
                        minDivisor[j] = i;
                    }
                }
            }
        }
    }

    vector<int> getFactor(int x) { //将x质因子分解  O(logx)
        vector<int>vec;
        while (x > 1) {
            int y = minDivisor[x];
            vec.push_back(y);
            while (x % y == 0)x /= y;
        }
        return vec;
    }

};
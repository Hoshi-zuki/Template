
//可自动推导 直接用 LIS(vector)就是答案  最长上升
template<typename T>
struct LIS {
    int ans;
    LIS(vector<T> &_vec) {
        vector<T>dp;
        for (auto &x : _vec) {
            auto it = lower_bound(dp.begin(), dp.end(), x);
            if (it == dp.end())dp.push_back(x);
            else *it = x;
        }
        ans = dp.size();
    }
    operator int()const {
        return ans;
    }
};
template<typename T>
LIS(vector<T> &_vec) -> LIS<T>;


//可自动推导 直接用 LDS(vector)就是答案  最长下降
template<typename T>
struct LDS {
    int ans;
    LDS(vector<T> &_vec) {
        vector<T>dp;
        for (int i = _vec.size() - 1;i >= 0;--i) {
            auto x = _vec[i];
            auto it = lower_bound(dp.begin(), dp.end(), x);
            if (it == dp.end())dp.push_back(x);
            else *it = x;
        }
        ans = dp.size();
    }
    operator int()const {
        return ans;
    }
};
template<typename T>
LDS(vector<T> &_vec) -> LDS<T>;


//可自动推导 直接用 LNDS(vector)就是答案  最长不降
template<typename T>
struct LNDS {
    int ans;
    LNDS(vector<T> &_vec) {
        vector<T>dp;
        for (auto &x : _vec) {
            auto it = upper_bound(dp.begin(), dp.end(), x);
            if (it == dp.end())dp.push_back(x);
            else *it = x;
        }
        ans = dp.size();
    }
    operator int()const {
        return ans;
    }
};
template<typename T>
LNDS(vector<T> &_vec) -> LNDS<T>;


//可自动推导 直接用 LNIS(vector)就是答案  最长不升
template<typename T>
struct LNIS {
    int ans;
    LNIS(vector<T> &_vec) {
        vector<T>dp;
        for (int i = _vec.size() - 1;i >= 0;--i) {
            auto x = _vec[i];
            auto it = upper_bound(dp.begin(), dp.end(), x);
            if (it == dp.end())dp.push_back(x);
            else *it = x;
        }
        ans = dp.size();
    }
    operator int()const {
        return ans;
    }
};
template<typename T>
LNIS(vector<T> &_vec) -> LNIS<T>;
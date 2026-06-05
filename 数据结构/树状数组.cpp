
// 一维 BIT  1-index
template<typename T>
struct Fenwick {
	int n;
	vector<T>a;
	Fenwick(int _n) {//维护索引 1~_n
		init(_n);
	}

	void init(int _n) {//维护索引 1~_n
		n = _n;
		a = vector<T>(n + 1, 0);
	}

	int lowbit(int x) {
		return (-x) & x;
	}

	void add(int index, T val) {//给索引index加上val
		assert(index > 0);
		for (int i = index;i <= n;i += lowbit(i)) {
			a[i] += val;
		}
	}

	T query(int index) {//查询1~index的和
		T res = 0;
		for (int i = index;i > 0;i -= lowbit(i)) {
			res += a[i];
		}
		return res;
	}

};


// 一维 BIT  0-index
template<typename T>
struct Fenwick {
	int n;
	vector<T>a;
	Fenwick(int _n) {//维护索引 0~_n-1
		init(_n);
	}

	void init(int _n) {//维护索引 0~_n-1
		n = _n;
		a = vector<T>(n + 1, 0);
	}

	int lowbit(int x) {
		return (-x) & x;
	}

	void add(int index, T val) {//给索引index加上val
		assert(index >= 0);
		index++;
		for (int i = index;i <= n;i += lowbit(i)) {
			a[i] += val;
		}
	}

	T query(int index) {//查询0~index的和
		index++;
		T res = 0;
		for (int i = index;i > 0;i -= lowbit(i)) {
			res += a[i];
		}
		return res;
	}

};


// 二维 BIT
template<typename T>
struct  Fenwick_2 {
	int n, m;
	vector<vector<T>>a;
	Fenwick_2(int _n, int _m) {//维护索引(1,1)~(_n,_m)
		init(_n, _m);
	}

	void init(int _n, int _m) {//维护索引(1,1)~(_n,_m)
		n = _n, m = _m;
		a = vector<vector<T>>(n + 1, vector<T>(m + 1, 0));
	}

	int lowbit(int x) {
		return (-x) & x;
	}

	void add(int x, int y, T val) {//给索引(x,y)加上val
		if (x == 0 || y == 0) {
			cerr << "ERROR: index in BIT is ZERO!" << endl;
		}
		for (int i = x;i <= n;i += lowbit(i)) {
			for (int j = y;j <= m;j += lowbit(j)) {
				a[i][j] += val;
			}
		}
	}

	T query(int x, int y) {//查询索引(1,1)~(x,y)的和
		T res = 0;
		for (int i = x;i > 0;i -= lowbit(i)) {
			for (int j = y;j > 0;j -= lowbit(j)) {
				res += a[i][j];
			}
		}
		return res;
	}

};
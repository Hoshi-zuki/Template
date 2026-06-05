template<typename T>//带自动推导，无需填
struct ST {
	int n;
	int B;
	const T(*cmp)(const T &, const T &);//替换为需要维护的信息,返回值不引用，格式如下面的函数模板
	vector<int>Lg;     //预处理log的值
	vector<vector<T>>st;

	ST(const vector<T> &_vec, const T(*_cmp)(const T &, const T &)) {
		init(_vec, _cmp);
	}

	void init(const vector<T> &_vec, const T(*_cmp)(const T &, const T &)) {
		n = _vec.size();
		cmp = _cmp;
		Lg = vector<int>(n + 1);
		for (int i = 1;i <= n;++i)Lg[i] = log2(i);
		B = Lg[n] + 1;
		st = vector<vector<T>>(n, vector<T>(B));
		for (int i = 0;i < n;++i)st[i][0] = _vec[i];
		for (int k = 1;k < B;++k) {
			for (int i = 0;i < n;++i) {
				st[i][k] = cmp(st[i][k - 1], st[min(i + (1 << k - 1), n - 1)][k - 1]);
			}
		}
	}

	T query(int l, int r) { //索引和传入的vector相匹配
		int k = Lg[r - l + 1];
		return cmp(st[l][k], st[r - (1 << k) + 1][k]);
	}

};
template<typename T>
ST(const vector<T> &_vec, const T(*_cmp)(const T &, const T &)) -> ST<T>;
template<typename T>
const T cmp_gcd(const T &_x, const T &_y) {
	return gcd(_x, _y);
}
template<typename T>
const T cmp_max(const T &_x, const T &_y) {
	return max(_x, _y);
}
template<typename T>
const T cmp_min(const T &_x, const T &_y) {
	return min(_x, _y);
}
template<typename T>
const T cmp_and(const T &_x, const T &_y) {
	return _x & _y;
}
template<typename T>
const T cmp_or(const T &_x, const T &_y) {
	return _x | _y;
}
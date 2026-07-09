
// 找s的所有循环移位字符串中字典序最小的
int Mini(string s) {//最小表示法，返回初始位置下标（0-index）
    int n = s.size();
    int i = 0, j = 1, k = 0;
    while (i < n && j < n) {
        k = 0;
        while (k < n && s[(i + k) % n] == s[(j + k) % n])k++;
        if (k == n)return min(i, j);
        if (s[(i + k) % n] > s[(j + k) % n])i = i + k + 1;
        else j = j + k + 1;
        if (i == j)j++;
    }
    return min(i, j);
}
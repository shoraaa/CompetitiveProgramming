#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int t[N], x[N], y[N], sorted_x[N];
ll sqr(ll x) {
	return x * x;
}
int intersect(int i, int j) {
	// duong doc x[i] co di qua hinh tron tam x[j], y[j] ban kinh y[j] ko
	return abs(sorted_x[i] - x[j]) < y[j];
}
int include(int i, int j) {
	// x[i], y[i] co nam hoan toan trong hinh tron tam x[j], y[j] ban kinh y[j] ko
	return sqr(x[i] - x[j]) + sqr(y[i] - y[j]) < sqr(y[j]);
}
struct segment_tree {
	int n;
	vector<vector<int>> st;
	int res, i;
	segment_tree(int n): n(n), st(n << 2) {}
	void update(int k, int l, int r) {
		int m = (l + r) >> 1;
		if (intersect(m, i)) 
			st[k].emplace_back(i);
		if (l == r) return;
		if (x[i] + y[i] <= sorted_x[m]) update(k << 1, l, m);
		if (x[i] - y[i] >= sorted_x[m]) update(k << 1 | 1, m + 1, r);
	}
	void erase(int k, int l, int r) {
		int m = (l + r) >> 1;
		if (intersect(m, res)) 
			st[k].erase(find(st[k].begin(), st[k].end(), res));
		if (l == r) return;
		if (x[res] + y[res] <= sorted_x[m]) erase(k << 1, l, m);
		if (x[res] - y[res] >= sorted_x[m]) erase(k << 1 | 1, m + 1, r);
	}
	void get(int k, int l, int r) {
		for (int j : st[k]) if (include(i, j))
			return res = j, erase(1, 1, n), void();
		if (l == r) return;
		int m = (l + r) >> 1;
		if (x[i] < sorted_x[m]) get(k << 1, l, m); 
		if (res != -1) return;
		if (x[i] > sorted_x[m]) get(k << 1 | 1, m + 1, r); 
	}
	void update(int id) {
		i = id, update(1, 1, n);
	}
	int get(int id) {
		return res = -1, i = id, get(1, 1, n), res;
	}
};
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> t[i] >> x[i] >> y[i], sorted_x[i] = x[i];
	sort(sorted_x + 1, sorted_x + n + 1);
	segment_tree st(n);
	for (int i = 1; i <= n; ++i)
		if (t[i] == 1) st.update(i);
		else cout << st.get(i) << '\n';
	return 0;
}


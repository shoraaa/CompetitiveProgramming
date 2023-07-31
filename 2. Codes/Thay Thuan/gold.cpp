#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5, oo = 1e9;
int a[N], tr[N];
int n, L, R;
struct segment_tree {
	vector<pair<ll, int>> st;
	int x, y;
	ll v;
	pair<ll, int> res;
	void init() {
		st.resize(n * 4, make_pair(-oo, -1));
	}
	void get(int k, int l, int r) {
		if (l > y || r < x) return;
		if (l >= x && r <= y)
			return res = max(res, st[k]), void();
		int m = (l + r) >> 1;
		get(k << 1, l, m);
		get(k << 1 | 1, m+1, r);
	}
	void update(int k, int l, int r) {
		if (l > x || r < x) return;
		if (l == r)
			return st[k] = {v, l}, void();
		int m = (l + r) >> 1;
		update(k << 1, l, m);
		update(k << 1 | 1, m+1, r);
		st[k] = max(st[k << 1], st[k << 1 | 1]);
	}
	pair<ll, int> get(int l, int r) {
		if (r < 0) return {0, -1};
		x = max(0, l), y = r, res = {0, -1};
		return get(1, 0, n-1), res;
	}
	void update(int i, ll val) {
		x = i, v = val;
		update(1, 0, n-1);
	} 
} st;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> L >> R;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	st.init();
	for (int i = 0; i < n; ++i) {
		auto p = st.get(i - R, i - L);
		st.update(i, p.first + a[i]);
		tr[i] = p.second;
	}
	auto p = st.get(0, n-1);
	cout << p.first << ' ';
//	stack<int> res;
//	for (int i = p.second; ~i; i = tr[i]) 
//		res.emplace(i);
//	cout << res.size() << '\n';
//	while (!res.empty())
//		cout << res.top() + 1 << ' ', res.pop();
	return 0;
}


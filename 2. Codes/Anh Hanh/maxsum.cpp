#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "maxsum";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const ll oo = 1e18;
struct V {
	pair<ll, int> max_prefix = {-oo, 0}, max_suffix = {-oo, 0};
	pair<ll, pair<int, int>> res = {-oo, {0, 0}};
	bool on_bit = 0;
	ll sum = 0;
};
struct Q {
	int l, r, v, i;
	Q(int l, int r, int v, int i): l(l), r(r), v(v), i(i) {}
	bool operator < (Q& u) const {
		return v > u.v;
	}
};
struct segment_tree {
	V merge(V& x, V& y) {
		V z;
		z.max_prefix = x.max_prefix;
		z.max_suffix = y.max_suffix;
		z.res = max(x.res, y.res);
		if (x.on_bit)
			z.max_prefix = max(z.max_prefix, {x.sum + y.max_prefix.first, y.max_prefix.second});
		if (y.on_bit)
			z.max_suffix = max(z.max_suffix, {y.sum + x.max_suffix.first, x.max_suffix.second});
		z.res = max(z.res, {x.max_suffix.first + y.max_prefix.first, {x.max_suffix.second, y.max_prefix.second}});
			
		z.on_bit = x.on_bit & y.on_bit;
		
		z.sum = x.sum + y.sum;
		return z;
	}
	int n, x, y, v; 
	V res;
	vector<V> st;
	segment_tree(int n): n(n), st(n << 2) {}
	void update(int k, int l, int r) {
		if (l > x || r < x) return;
		if (l == r) 
			return st[k].max_prefix = st[k].max_suffix = {v, l + 1},
						 st[k].res = {v, {l + 1, l + 1}},
						 st[k].on_bit = 1, st[k].sum = v, void();
						 
		int m = (l + r) >> 1;
		update(k << 1, l, m);
		update(k << 1 | 1, m+1, r);
		st[k] = merge(st[k << 1], st[k << 1 | 1]);
	}
	void get(int k, int l, int r) {
		if (l > y || r < x) return;
		if (l >= x && r <= y)
			return res = merge(res, st[k]), void(); 
		int m = (l + r) >> 1;
		get(k << 1, l, m);
		get(k << 1 | 1, m+1, r);
	}
	void update(int pos, int val) {
		x = pos, v = val;
		update(1, 0, n-1);
	}
	V get(int l, int r) {
		x = l, y = r, res = V();
		get(1, 0, n-1);
		return res;
	}
};
const int N = 4e5 + 5;
int a[N];
int n, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	int T;
	cin >> T;
	
	cin >> n >> q;
	vector<int> c(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i], c[i] = a[i];
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	vector<vector<int>> idx(c.size());
	for (int i = 0; i < n; ++i)
		idx[lower_bound(c.begin(), c.end(), a[i]) - c.begin()].emplace_back(i);
	vector<Q> que;
	for (int i = 0, l, r, v; i < q; ++i) 
		cin >> l >> r >> v, l--, r--,
		que.emplace_back(l, r, v, i);
	sort(que.begin(), que.end());
	vector<V> res(q);
	segment_tree st(n);
	int cur = c.size() - 1;
	for (Q& qu : que) {
		while (~cur && c[cur] >= qu.v) {
			for (int i : idx[cur]) st.update(i, a[i]);
			cur--;
		}
		res[qu.i] = st.get(qu.l, qu.r);
	}
	for (int i = 0; i < q; ++i) {
		if (res[i].res.first == -oo) cout << 0 << '\n';
		else cout << res[i].res.second.first << ' ' << res[i].res.second.second << '\n';
	}
	return 0;
}


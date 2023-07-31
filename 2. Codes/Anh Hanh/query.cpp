#include <bits/stdc++.h>
using namespace std;
void file() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	const string FILE_NAME = "query";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3e5 + 5;
const int oo = 1e9;
vector<int> G[N];
int in[N], out[N], dep[N], a[N];
const int K = 15;
struct segment_tree {
	array<int, 15> merge(array<int, 15>& u, array<int, 15>& v) {
		array<int, 15> res;
		int i = 0, j = 0, k = 0;
		while (k < K && i < K && j < K)
			if (u[i] > v[j]) res[k++] = u[i++];
			else res[k++] = v[j++];
		while (k < K && i < K)
			res[k++] = u[i++];
		while (k < K && j < K)
			res[k++] = v[j++];
		return res; 
	}
	struct node {
		array<array<int, 15>, 2> max;
		array<int, 2> val;
	};
	vector<node> st;
	int n, x, y, d, v;
	array<int, 15> res;
	array<int, 2> val;
	segment_tree(int n): n(n), st(n * 2 - 1) { build(0, 0, n-1); }
	pair<int, int> build(int k, int l, int r) {
		if (l == r) {
			for (int i = 0; i < K; ++i) 
					st[k].max[0][i] = st[k].max[1][i] = -oo;
			if (dep[a[l]] == 0) {
				st[k].max[0][0] = 0;
				return {1, 0};
			} else {
				st[k].max[1][0] = 0;
				return {0, 1};
			}
		}
		int m = (l + r) >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
		auto u = build(lc, l, m);
		auto v = build(rc, m+1, r);
		int m0 = min(u.first + v.first, K),
				m1 = min(u.second + v.second, K);
		for (int i = m0; i < K; ++i) st[k].max[0][i] = -oo;
		for (int i = m1; i < K; ++i) st[k].max[1][i] = -oo;
		return {m0, m1};
	}
	void add(int k, int l, int r) {
		if (l > y || r < x) return;
		if (l >= x && r <= y) {
			st[k].val[d] += v, st[k].val[d ^ 1] -= v;
			for (int i = 0; i < K; ++i) 
				st[k].max[d][i] += v;
			for (int i = 0; i < K; ++i) 
				st[k].max[d ^ 1][i] -= v;
			return;
		}
		int m = (l + r) >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
		add(lc, l, m);
		add(rc, m+1, r);
		st[k].max[0] = merge(st[lc].max[0], st[rc].max[0]);
		for (int i = 0; i < K; ++i) 
				st[k].max[0][i] += st[k].val[0];
		st[k].max[1] = merge(st[lc].max[1], st[rc].max[1]);
		for (int i = 0; i < K; ++i) 
				st[k].max[1][i] += st[k].val[1];
	}
	void get(int k, int l, int r) {
		if (l == r) {
			v += st[k].val[d];
			return;
		}
		v += st[k].val[d];
		int m = (l + r) >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
		if (x <= m) get(lc, l, m);
		else get(rc, m+1, r);
	}
	void kth(int k, int l, int r) {
		if (l > y || r < x) return;
		if (l >= x && r <= y) {
			auto zero = st[k].max[0], one = st[k].max[1];
			for (int i = 0; i < K; ++i) 
				zero[i] += val[0];
		for (int i = 0; i < K; ++i) 
				one[i] += val[1];
			zero = merge(zero, one);
			res = merge(res, zero);
			return;
		}
		val[0] += st[k].val[0];
		val[1] += st[k].val[1];
		int m = (l + r) >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
		kth(lc, l, m);
		kth(rc, m+1, r);
		val[0] -= st[k].val[0];
		val[1] -= st[k].val[1];
	}
	void add(int u, int k) {
		x = in[u], y = out[u], v = k, d = dep[u];
		add(0, 0, n-1);
	}
	int get(int u) {
		x = in[u], v = 0, d = dep[u];
		get(0, 0, n-1);
		return v;
	}
	int kth(int u, int k) {
		x = in[u], y = out[u], val[0] = val[1] = 0;
		if (k > y - x + 1) return 0;
		for (int i = 0; i < K; ++i)
			res[i] = -oo;
		
		kth(0, 0, n-1);
		return res[k - 1];
	}
};
int n, q, t = 0;
void build(int u = 0, int e = -1) {
	if (e != -1) dep[u] = (dep[e] + 1) & 1;
	in[u] = t++; a[in[u]] = u;
	for (int v : G[u]) if (v != e)
		build(v, u);
	out[u] = t - 1;
}
int main() {
	file();
	cin >> n >> n;
	for (int u = 1, p; u < n; ++u)
		cin >> p, p--,
		G[u].emplace_back(p),
		G[p].emplace_back(u);
	build(); 
	segment_tree st(n);
	cin >> q; string s;
	for (int i = 0, u, k; i < q; ++i) {
		cin >> s >> u, u--;
		if (s[0] == 'g') {
			cout << st.get(u) << ' ';
		} else {
			cin >> k;
			if (s[0] == 'a') st.add(u, k);
			else cout << st.kth(u, k) << ' ';
		} 
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	const string FILE_NAME = "talltree";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 5e5 + 5, M = 998244353;
void add(int& x, int y) {
	x += y; if (x >= M) x -= M;
}
void sub(int& x, int y) {
	x -= y; if (x < 0) x += M;
}
int sum(int x, int y) {
	x += y; if (x >= M) x -= M; return x;
}
int dif(int x, int y) {
	x -= y; if (x < 0) x += M; return x;
}
int mul(ll x, ll y) {
	return x * y % M;
}
struct node {
	int k = 0, l = 0, s = 0, d = 0, sum = 0;
};
void add(node& x, node& y) {
	add(x.k, y.k), add(x.l, y.l), add(x.s, y.s);
}
void sub(node& x, node& y) {
	sub(x.k, y.k), sub(x.l, y.l), sub(x.s, y.s);
}
vector<int> G[N];
int in[N], out[N], dep[N], pos[N];
struct segment_tree {
	vector<node> st;
	int n, x, y, d;
	node v;
	segment_tree(int n): n(n), st(n * 2 - 1) { build(0, 0, n-1); }
	void build(int k, int l, int r) {
		if (l == r) return st[k].d = dep[pos[l]], void();
		int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
		build(lc, l, m);
		build(rc, m+1, r);
		st[k].d = sum(st[lc].d, st[rc].d);
	}
	void update(int k, int l, int r) {
		if (l > y || r < x) return;
		if (l >= x && r <= y) {
			add(st[k], v);
			add(st[k].sum, dif(mul(sum(v.k, v.s), r-l+1), mul(st[k].d, v.l)));
			return;
		}
		int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
		update(lc, l, m);
		update(rc, m+1, r);
		st[k].sum = sum(st[lc].sum, st[rc].sum);
		add(st[k].sum, dif(mul(sum(st[k].k, st[k].s), r-l+1), mul(st[k].d, st[k].l)));
	}
	void val(int k, int l, int r) {
		add(v, st[k]);
		if (l == r) return;
		int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
		if (x <= m) val(lc, l, m);
		else val(rc, m+1, r);
	}
	void get(int k, int l, int r) {
		if (l > y || r < x) return;
		if (l >= x && r <= y) {
			add(v.sum, st[k].sum);
			add(v.sum, dif(mul(sum(v.k, v.s), r-l+1), mul(st[k].d, v.l)));
			return;
		}
		int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
		add(v, st[k]);
		get(lc, l, m);
		get(rc, m+1, r);
		sub(v, st[k]);
	}
	void upd(int u, int k, int l) {
		x = in[u], y = out[u], d = dep[u];
		v.k = k, v.l = l, v.s = mul(d, v.l);
		update(0, 0, n-1);
	}
	int val(int u) {
		x = in[u], d = dep[u];
		v.k = v.l = v.s = 0;
		val(0, 0, n-1);
		return dif(sum(v.k, v.s), mul(d, v.l));
	}
	int get(int u) {
		x = in[u], y = out[u];
		v.k = v.l = v.s = v.sum = 0;
		get(0, 0, n-1);
		return v.sum;
	}
};
int n, q, t = 0;
void build(int u = 0, int e = -1) {
	if (e != -1) dep[u] = dep[e] + 1;
	in[u] = t++; pos[in[u]] = u;
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
	for (int i = 0, u, l, k; i < q; ++i) {
		cin >> s >> u, u--;
		if (s[0] == 'g') {
			cout << st.val(u) << ' ';
		} else {
			if (s[0] == 'a') cin >> k >> l, 
				k %= M, l %= M, 
				k = k < 0 ? k + M : k,
				l = l < 0 ? l + M : l,
				st.upd(u, k, l);
			else cout << st.get(u) << ' ';
		} 
	}
	return 0;
}
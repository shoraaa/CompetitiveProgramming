#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "costquery";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
struct E {
	int u, v, w;
	E(int u, int v, int w): u(u), v(v), w(w) {}
	bool operator < (E& e) const {
		return w < e.w;
	}
};
struct union_set {
	int n;
	ll res;
	vector<int> li, sz;
	union_set(int n): n(n), li(n), sz(n), res(0) {
		iota(li.begin(), li.end(), 0);
		fill(sz.begin(), sz.end(), 1);
	}
	int find(int u) {
		if (u == li[u]) return u;
		return li[u] = find(li[u]);
	}
	int unite(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return 0;
		if (sz[u] < sz[v]) swap(u, v);
		li[v] = u; 
		res -= ll(sz[u]) * (sz[u] - 1) / 2;
		res -= ll(sz[v]) * (sz[v] - 1) / 2;
		sz[u] += sz[v]; 
		res += ll(sz[u]) * (sz[u] - 1) / 2;
		return 1;
	}
};
int n, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n >> q;
	vector<E> edg;
	vector<int> c;
	for (int i = 0, u, v, w; i < n-1; ++i)
		cin >> u >> v >> w, u--, v--,
		edg.emplace_back(u, v, w),
		c.emplace_back(w);
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	sort(edg.begin(), edg.end());
	int m = c.size(); 
	vector<ll> f(m);
	union_set dsu(n);
	for (int i = 0, j = 0; i < m; ++i) {
		while (j < n-1 && edg[j].w <= c[i]) dsu.unite(edg[j].u, edg[j].v), j++;
		f[i] = dsu.res;
	}
	for (int i = 0, l, r; i < q; ++i) {
		cin >> l >> r;
		l = lower_bound(c.begin(), c.end(), l) - c.begin(),
		r = upper_bound(c.begin(), c.end(), r) - c.begin() - 1;
		if (l == n || r == -1) cout << 0 << ' ';
		else cout << f[r] - (l ? f[l-1] : 0) << ' ';
	}
	return 0;
}


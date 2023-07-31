#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "distance";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3e5 + 5;
int par[N][20], dep[N];
ll dis[N];
struct C {
	int v, w;
	C(int v, int w): v(v), w(w) {}
};
int n, q;
vector<C> G[N];
int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 19; ~i; --i) if (dep[par[u][i]] >= dep[v]) 
		u = par[u][i];
	if (u == v) return u;
	for (int i = 19; ~i; --i) if (par[u][i] != par[v][i])
		u = par[u][i], v = par[v][i];
	return par[u][0];
}
ll d(int u, int v) {
	return dis[u] + dis[v] - dis[lca(u, v)] * 2;
}
void build(int u = 0, int e = 0, int w = 0) {
	par[u][0] = e;
	for (int i = 1; i < 20; ++i) 
		par[u][i] = par[par[u][i-1]][i-1];
	dep[u] = dep[e] + 1;
	dis[u] = dis[e] + w;
	for (C& c : G[u]) if (c.v != e) 
		build(c.v, u, c.w);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	int t;
	cin >> t >> n;
	for (int i = 0, u, v, w; i < n-1; ++i)
		cin >> u >> v >> w, u--, v--,
		G[u].emplace_back(v, w),
		G[v].emplace_back(u, w);
	build();
	cin >> q;
	for (int i = 0, u, v; i < q; ++i) 
		cin >> u >> v, u--, v--,
		cout << d(u, v) << '\n';
	return 0;
}


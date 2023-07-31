#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "biconnected";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 25 * 1e4 + 5;
struct C {
	int v, i;
	C(int v, int i = -1): v(v), i(i) {}
};
vector<C> G[N];
vector<int> lea;
vector<pair<int, int>> bri;
int vis[N], tin[N], low[N], lin[N], siz[N];
int n, m, t = 0;
int find(int u) {
	if (u == lin[u]) return u;
	return lin[u] = find(lin[u]);
}
void unite(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return;
	if (siz[u] < siz[v]) swap(u, v);
	lin[v] = u; siz[u] += siz[v];
}
void dfs(int u, int e = -1) {
	vis[u] = 1;
	tin[u] = low[u] = t++;
	for (C& c : G[u]) if (c.i != e) {
		if (vis[c.v]) 
			unite(u, c.v),
			low[u] = min(low[u], tin[c.v]);
		else {
			dfs(c.v, c.i);
			low[u] = min(low[u], low[c.v]);
			if (low[c.v] <= tin[u]) unite(u, c.v);
			else bri.emplace_back(u, c.v);
		}
	}
}
void dfs_t(int u, int p = -1) {
	if (G[u].size() == 1)
		lea.emplace_back(u);
	for (C& c : G[u]) if (c.v != p)
		dfs_t(c.v, u);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();				
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 0, u, v; i < m; ++i)
			cin >> u >> v, u--, v--,
			G[u].emplace_back(v, i),
			G[v].emplace_back(u, i);
		bri.clear();
		memset(vis, 0, sizeof(vis));
		iota(lin, lin + n, 0);
		fill(siz, siz + n, 1);
		t = 0;
		for (int i = 0; i < n; ++i) 
			if (!vis[i]) dfs(i);
		for (int i = 0; i < n; ++i)
			G[i].clear();
		for (auto& p : bri) 
			G[find(p.first)].emplace_back(find(p.second)),
			G[find(p.second)].emplace_back(find(p.first));
		int root = find(0);
		if (G[root].size() == 1) root = G[root][0].v;
		lea.clear();
		dfs_t(root);
		int v = lea.size();
		cout << (v + 1) / 2 << '\n';
		for (int i = 0; i < v / 2; ++i)
			cout << lea[i] + 1 << ' ' << lea[v/2+i] + 1 << '\n';
		if (v & 1) cout << lea[0] + 1 << ' ' << lea[v/2] + 1<< '\n'; 
	//	if (v & 1) cout << lea[v-1] + 1 << ' ' << root + 1 << '\n'; 
		for (int i = 0; i < n; ++i)
			G[i].clear();
	}
	// printf("2\n2 6\n7 8\n 0");
	return 0;
}


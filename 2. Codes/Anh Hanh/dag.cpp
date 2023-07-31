#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "dag";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 5e5 + 5;
struct C {
	int v, i;
	C(int v, int i = -1): v(v), i(i) {}
};
vector<C> G[N];
vector<int> back;
int vis[N], tin[N], low[N], res[N], des[N];
int n, m, t = 0;
int dfs_c(int u) {
	vis[u] = 1;
	for (C& c : G[u]) if (!des[c.i] && vis[c.v] != 2) 
		if (vis[c.v] == 1 || !dfs_c(c.v)) return 0;
	return vis[u] = 2;
}
int check() {
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < n; ++i) 
		if (!vis[i] && !dfs_c(i)) return 0;
	return 1; 
}
void dfs(int u, int e = -1) {
	vis[u] = 1;
	tin[u] = low[u] = t++;
	for (C& c : G[u]) if (!des[c.i] && c.i != e) {
		if (!vis[c.v] || tin[c.v] > tin[u]) {
			des[c.i] = 1; // xoa canh nay di luon
			if (!vis[c.v]) dfs(c.v, c.i);
			low[u] = min(low[u], low[c.v]);
		} else 
			back.emplace_back(c.i),
			low[u] = min(low[u], tin[c.v]);
	} ;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();				
	cin >> n >> m;
	int self_edge = 0;
	for (int i = 0, u, v; i < m; ++i)
		cin >> u >> v, u--, v--,
		G[u].emplace_back(v, i),
		self_edge |= u == v;
	if (self_edge) 
		return cout << -1, 0;
	for (int d = 1; !check(); ++d) {
		memset(vis, 0, sizeof(vis)); t = 0;
		back.clear();
		for (int i = 0; i < n; ++i) 
			if (!vis[i]) dfs(i);
		for (int i : back) res[i] = d;
	}
	cout << *max_element(res, res + m) + 1 << '\n';
	for (int i = 0; i < m; ++i)
			cout << res[i] + 1 << ' ';
	return 0;
}


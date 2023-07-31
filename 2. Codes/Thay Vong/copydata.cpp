#include <bits/stdc++.h>
using namespace std;
void file() {
  const string FILE_NAME = "copydata";
  freopen((FILE_NAME + ".in").c_str(), "r", stdin);
  freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3e5 + 5;
int n, a, b, f[N];
vector<int> adj[N], path;
bool op[N];
bool dfs(int u, int p = 0) {
	op[u] = 1; path.emplace_back(u);
	if (u == b) return 1;
	for (int &v : adj[u]) if (v != p)
		if (dfs(v, u)) return 1;
	op[u] = 0; path.pop_back();
	return 0;
}
void dfs2(int u, int p = 0) {
	f[u] = 0;
	vector<int> g;
	for (int &v : adj[u]) if (v != p && !op[v]) 
		dfs2(v, u), g.emplace_back(v);
	if (g.size()) {
		sort(g.begin(), g.end(), [&](int &x, int &y) {return f[x] > f[y];});
		for (int i = 0; i < g.size(); ++i)	
			f[u] = max(f[u], f[g[i]] + i + 1);
	}
}
bool vis[N];
bool check(int t) {
	for (int v : path) vis[v] = 0;
	queue<pair<int, int>> que; 
	que.emplace(a, 0); vis[a] = 1;
	que.emplace(b, 0); vis[b] = 1;
	while (que.size()) {
		pair<int, int> cur = que.front(); que.pop();
		if (f[cur.first] + cur.second > t) return 0;
		int nt = (f[cur.first] + 1 + cur.second <= t) ? 0 : 1;
		for (int &v : adj[cur.first]) if (!vis[v] && op[v])
			vis[v] = 1, que.emplace(v, cur.second + nt + 1);
	}
	return 1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n >> a >> b;
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	dfs(a);
	for (int &v : path) 
	  dfs2(v);
	int lo = 0, hi = n, res;
	while (lo <= hi) {
		int mi = (lo + hi) / 2;
		if (check(mi)) res = mi, hi = mi - 1;
		else lo = mi + 1;
	}
	cout << res;
	return 0;
}
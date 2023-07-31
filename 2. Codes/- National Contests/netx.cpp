#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
vector<pair<int, int>> adj[N], edges;
vector<int> tree[N];
int n, m;

int in[N], low[N], bridge[N]; int t = 0;
void build(int u, int p = -1) {
	in[u] = low[u] = ++t;
	for (auto& e : adj[u]) {
		int v, i; tie(v, i) = e;
		if (v == p) continue;
		if (in[v]) low[u] = min(low[u], in[v]);
		else {
			build(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > in[u]) bridge[i] = 1;
		}
	}
}

int comp[N]; int compid = 0;
void dfs(int u) {
	comp[u] = compid;
	for (auto& e : adj[u]) {
		int v, i; tie(v, i) = e;
		if (~comp[v] || bridge[i]) continue;
		dfs(v);
	}
}

int leaf = 0;
void dfs2(int u, int p = -1) {
	leaf += tree[u].size() == 1;
	for (int v : tree[u]) if (v != p)
		dfs2(v, u);
}

int main() {
  if (fopen("netx.inp", "r"))
    freopen("netx.inp", "r", stdin),
    freopen("netx.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0, u, v; i < m; ++i)
		cin >> u >> v, u--, v--,
		adj[u].emplace_back(v, i),
		adj[v].emplace_back(u, i),
		edges.emplace_back(u, v);
	build(0);
	memset(comp, -1, sizeof(comp));
	for (int u = 0; u < n; ++u) if (!~comp[u]) {
		dfs(u); compid++;
	}
	for (int i = 0, u, v; i < m; ++i) {
		tie(u, v) = edges[i];
		if (!bridge[i]) continue;
		u = comp[u], v = comp[v];
		tree[u].emplace_back(v);
		tree[v].emplace_back(u);
	}
	dfs2(0);
	if (leaf == 1) cout << 0;
	else cout << (leaf + 1) / 2;
	return 0;
}

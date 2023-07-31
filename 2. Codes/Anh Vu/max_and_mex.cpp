#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5, inf = 1e9;
int n;
int a[N], pos[N], par[N][18], dep[N];
vector<int> adj[N];
void dfs(int u = 0, int p = -1) {
  if (p != -1) {
    par[u][0] = p, dep[u] = dep[p] + 1;
    for (int k = 1; k < 18; ++k)
      par[u][k] = par[par[u][k-1]][k-1];
  }
  for (int v : adj[u]) if (v != p)
    dfs(v, u);
}
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = 17; ~k; --k) 
    if (dep[par[u][k]] >= dep[v]) u = par[u][k];
  if (u == v) return u;
  for (int k = 17; ~k; --k)
    if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
  return par[u][0];
}
int dis(int u, int v) {
  return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}
int on_path(int x, int y, int z) {
  return dis(x, z) + dis(z, y) == dis(x, y);
}
int simple_path(int x, int y, int z) {
  return on_path(x, y, z) || on_path(x, z, y) || on_path(y, z, x);
}
void walk(int& x, int& y, int z) {
  if (on_path(x, y, z)) return;
  if (dis(x, z) < dis(y, z)) x = z;
  else y = z;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	ll c, d;
  cin >> n >> c >> d;
  for (int u = 0; u < n; ++u)
    cin >> a[u], pos[a[u]] = u;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  dfs();
  ll res = c + d*(n-1); 
  int head = pos[0], tail = pos[0], cur_max = n-1;
  for (int u = 1; u < n; ++u) {
    if (!simple_path(head, tail, pos[u])) break;
    walk(head, tail, pos[u]);
    while (!simple_path(head, tail, pos[cur_max])) cur_max--;
    res = max(res, c*(u+1) + d*cur_max);
  }
  cout << res;
	return 0;
}


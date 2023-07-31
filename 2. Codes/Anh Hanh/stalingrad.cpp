#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 4e5 + 5;
int root[N], in[N], sz[N], dep[N], par[N][20], t = 0;
int n, q, O; set<pair<int, int>> st[N];
vector<int> adj[N];
void dfs(int u, int p, int r) {
  par[u][0] = p;
  for (int k = 1; k < 20; ++k)
    par[u][k] = par[par[u][k-1]][k-1];
  root[u] = r; in[u] = t++; sz[u] = 1; dep[u] = dep[p] + 1;
  for (int v : adj[u]) if (v != p)
    dfs(v, u, r), sz[u] += sz[v];
}
int lca(int u, int v) {
  if (dep[u] > dep[v]) swap(u, v);
  for (int k = 19; ~k; --k) if (dep[par[v][k]] >= dep[u]) v = par[v][k];
  if (v == u) return u;
  for (int k = 19; ~k; --k) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
  return par[u][0];
}
int get(int u) {
  if (st[u].empty()) return 0;
  int lo = st[u].begin()->second, hi = st[u].rbegin()->second;
  return sz[lca(lo, hi)] - st[u].size();
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("stalingrad.inp", "r"))
    freopen("stalingrad.inp", "r", stdin),
    freopen("stalingrad.out", "w", stdout);
  cin >> O >> n >> q;
  for (int i = 1, p; i < n; ++i) {
    cin >> p; p--;
    adj[i].emplace_back(p);
    adj[p].emplace_back(i);
  }
  for (int v : adj[0])
    dfs(v, 0, v);
  int res = 0, tot = 0;
  for (int i = 0, u; i < q; ++i) {
    char c; cin >> c >> u; u--;
    res -= !st[root[u]].empty(); tot -= get(root[u]);
    if (c == '+') st[root[u]].insert({in[u], u});
    else st[root[u]].erase({in[u], u});
    res += !st[root[u]].empty(); tot += get(root[u]);
    cout << res << ' ' << tot << '\n';
  }
	return 0;
}


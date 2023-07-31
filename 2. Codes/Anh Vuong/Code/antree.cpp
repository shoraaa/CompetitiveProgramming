#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5, K = 17;
vector<pair<int, int>> adj[N];
int n, q;

int dep[N], par[N][K + 1], w[N], edges[N];
ll dis[N], sum[N][K + 1];

void dfs(int u = 1, int p = 0) {
  for (auto& pi : adj[u]) {
    int v, i; tie(v, i) = pi;
    if (v == p) continue;
    dep[v] = dep[u] + 1;
    dis[v] = dis[u] + w[i];
    sum[v][0] = w[i];
    par[v][0] = u; edges[v] = i;
    for (int i = 1; i <= K; ++i)
      par[v][i] = par[par[v][i - 1]][i - 1],
      sum[v][i] = sum[v][i - 1] + sum[par[v][i - 1]][i - 1];
    dfs(v, u);
  }
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int i = K; ~i; --i) if (dep[par[u][i]] >= dep[v]) u = par[u][i];
  if (u == v) return u;
  for (int i = K; ~i; --i) if (par[u][i] != par[v][i])
    u = par[u][i], v = par[v][i];
  return par[u][0];
}

int get(int u, int v, ll t) {
  for (int i = K; ~i; --i) if (t >= sum[u][i])
    t -= sum[u][i], u = par[u][i];
  return edges[u] + 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("antree.in", "r"))  
    freopen("antree.in", "r", stdin),
    freopen("antree.out", "w", stdout);
  
  cin >> n;
  for (int i = 0, u, v; i < n-1; ++i) {
    cin >> u >> v >> w[i];
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
  }
  dep[0] = -1; dfs();
  cin >> q; ll t;
  for (int i = 0, u, v; i < q; ++i) {
    cin >> u >> v >> t;
    int z = lca(u, v);
    ll d1 = dis[u] - dis[z], d2 = dis[v] - dis[z];
    if (t >= d1 + d2) cout << -1 << '\n';
    else if (t < d1) cout << get(u, z, t) << '\n';
    else t -= d1, cout << get(v, z, d2 - t - 1) << '\n';
  }
  
	return 0;
}


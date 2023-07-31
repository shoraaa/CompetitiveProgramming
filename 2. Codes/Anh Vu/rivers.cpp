#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 100 + 5;
const ll inf = 1e16 + 5;
struct AdjacentEdge {
  int v, w;
  AdjacentEdge(int v = 0, int w = 0): v(v), w(w) {}
};
vector<AdjacentEdge> adj[N];
ll a[N], dep[N], sum[N], par[N], cc[N];
int siz[N];
ll smul[N];
int n, K;
void dfs(int u = 0) {
  sum[u] = a[u], smul[u] = dep[u] * a[u], siz[u] = 1;
  for (int i = 1; i <= cc[u]; ++i) {
    auto c = adj[u][i];
    dep[c.v] = dep[u] + c.w,
    par[c.v] = u,
    dfs(c.v),
    siz[u] += siz[c.v],
    sum[u] += sum[c.v],
    smul[u] += smul[c.v];
  }
}
ll dp[N][N][N], f[N][N], g[N][N];
void calc(int u = 0) {
  for (int i = 1; i <= cc[u]; ++i) {
    auto c = adj[u][i];
    calc(c.v);
  }
  for (int p = par[u]; ~p; p = par[p]) {
    for (int k = 0; k <= K; ++k) 
      for (int i = 0; i <= cc[u]; ++i) 
        f[k][i] = g[k][i] = inf;
    f[0][0] = (dep[u] - dep[p]) * a[u];
    for (int k = 0; k <= K; ++k) {
      for (int i = 1; i <= cc[u]; ++i) { 
        auto c = adj[u][i];
        for (int t = 0; t <= k; ++t)
          f[k][i] = min(f[k][i], f[k-t][i-1] + dp[c.v][p][t]);
      }
      dp[u][p][k] = f[k][cc[u]];
    }
    g[1][0] = 0;
    for (int k = 1; k <= K; ++k) {
      for (int i = 1; i <= cc[u]; ++i) { 
        auto c = adj[u][i];
        for (int t = 0; t <= k-1; ++t)
          g[k][i] = min(g[k][i], g[k-t][i-1] + dp[c.v][u][t]);
      }
      dp[u][p][k] = min(f[k][cc[u]], g[k][cc[u]]);
    }
  }
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> K;
  for (int i = 0; i <= n; ++i)
    adj[i].emplace_back();
  for (int i = 1, w, p, d; i <= n; ++i) 
    cin >> w >> p >> d,
    adj[p].emplace_back(i, d),
    a[i] = w;
  for (int i = 0; i <= n; ++i)
    cc[i] = adj[i].size() - 1;
  par[0] = -1; dfs();
  for (int i = 1; i <= cc[0]; ++i) {
    auto c = adj[0][i];
    calc(c.v);
  }
  for (int k = 0; k <= K; ++k)
    for (int i = 0; i <= cc[0]; ++i) 
      g[k][i] = inf;
  g[0][0] = 0;
  for (int k = 0; k <= K; ++k) {
    for (int i = 1; i <= cc[0]; ++i) { 
      auto c = adj[0][i];
      for (int t = 0; t <= min(k, siz[cc[c.v]] + 1); ++t)
        g[k][i] = min(g[k][i], g[k-t][i-1] + dp[c.v][0][t]);
    }
  }
  cout << g[K][cc[0]];
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 55;
vector<tuple<int, int, int>> edges;
int n, m;
ll d[N];
int cmin(ll& x, ll y) {
  return x > y ? x = y, 1 : 0; 
}
void task1() {
  memset(d, 0x3f, sizeof(d)); ll inf = d[0];
  d[0] = 0;
  int u, v, w;
  for (int i = 0; i < n-1; ++i)
    for (auto& e : edges)
      tie(u, v, w) = e,
      cmin(d[v], d[u] + w);
  if (d[n-1] == inf) cout << -1 << '\n';
  else cout << d[n-1] << '\n';
}
struct Adjacent {
  int v, w;
  Adjacent(int v, int w): v(v), w(w) {}
};
vector<Adjacent> adj[N][12]; 
ll dp[1 << 12][12][50];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; string task;
  cin >> T;
  while (T--) {
    cin >> n >> m; edges.clear();
    for (int i = 0, u, v, w; i < m; ++i) 
      cin >> u >> v >> w, u--, v--,
      edges.emplace_back(u, v, w);
    cin >> task;
    if (task == "False") {
      task1(); continue;
    }

    for (int u = 0; u < n; ++u) for (int w = 0; w < 12; ++w)
      adj[u][w].clear();
    for (int i = 0, u, v, w; i < m; ++i) {
      tie(u, v, w) = edges[i];
      if (w % 13 == 0) continue;
      adj[u][w % 13 - 1].emplace_back(v, w);
    }
    
    memset(dp, 0x3f, sizeof(dp)); ll inf = dp[0][0][0];
    for (int w = 0; w < 12; ++w) for (auto& c : adj[0][w])
      if (dp[1 << w][w][c.v] > 1) dp[1 << w][w][c.v] = c.w;
      
    for (int msk = 1; msk < 1 << 12; ++msk) for (int l = 0; l < 12; ++l) {
      for (int u = 0; u < n; ++u) if (dp[msk][l][u] != inf) {
        ll dis = dp[msk][l][u];
        for (int w = 0; w < 12; ++w) {
          int nxt = (l + w + 2) % 13 - 1;
          if (nxt == -1 || (msk >> nxt & 1)) continue;
          for (auto& c : adj[u][w])
            cmin(dp[msk | (1 << nxt)][nxt][c.v], dis + c.w);
        }
      }
    }
    ll res = inf;
    for (int msk = 0; msk < 1 << 12; ++msk) for (int l = 0; l < 12; ++l)
      cmin(res, dp[msk][l][n-1]);
    if (res == inf) cout << -1 << '\n';
    else cout << res << '\n';
  }
	return 0;
}


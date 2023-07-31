#include<bits/stdc++.h>
#define cout cerr
using namespace std;
using ll = long long;
const int N = 1e3 + 5, inf = 1e9 + 10;
struct AdjacentEdge {
  int v, w;
  AdjacentEdge(int v, int w): v(v), w(w) {}
  bool operator < (const AdjacentEdge& c) const {
    return v < c.v;
  }
};
vector<AdjacentEdge> adj[N];
int d[N], dp[N][105], in[N];
int n, m, t, K, C;
int call(int u, int l) {
  if (l < 0 || l > C) return 0;
  if (dp[u][l] != -1) return dp[u][l];
  int res = 0;
  if (u == t) res++; 
  for (auto& c : adj[u]) {
    res += call(c.v, l + d[u] + c.w - d[c.v]);
    if (res > inf) res = inf;
  }
  return dp[u][l] = res;
}
vector<int> pat;
void trace(int u, int l) {
  pat.emplace_back(u);
  if (u == t) K--;
  if (K == 0) return;
  for (auto& c : adj[u]) {
    int nxt = call(c.v, l + d[u] + c.w - d[c.v]);
    if (nxt >= K) 
      return trace(c.v, l + d[u] + c.w - d[c.v]), void();
    else K -= nxt;
  }
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> t >> K, t--, C = inf;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--, C = min(C, w),
    adj[u].emplace_back(v, w);
  for (int u = 0; u < n; ++u)
    sort(adj[u].begin(), adj[u].end());
  queue<int> q; 
  fill(begin(d), end(d), inf);
  q.emplace(0); d[0] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop(); in[u] = 0;
    for (auto& c : adj[u]) if (d[u] + c.w < d[c.v]) {
      d[c.v] = d[u] + c.w;
      if (!in[c.v]) 
        q.emplace(c.v), in[c.v] = 1;
    }
  }
  memset(dp, -1, sizeof(dp));
  if (K > call(0, 0))
    return cout << -1, 0;
  trace(0, 0);
  cout << pat.size() << '\n';
  for (int u : pat)
    cout << u + 1 << ' ';
	return 0;
}


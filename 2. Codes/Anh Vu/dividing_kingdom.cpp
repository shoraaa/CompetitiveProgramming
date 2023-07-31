#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 5;
const ll llinf = 1e16;
struct AdjacentEdge {
  int v, w;
  AdjacentEdge(int v = 0, int w = 0): v(v), w(w) {}
};
vector<AdjacentEdge> adj[N];
vector<ll> bp[N], bs[N], dp[N], ds[N];
int cc[N];
int n;
ll res = llinf;
void build(int u = 0) {
  for (int i = 1; i <= cc[u]; ++i) {
    auto c = adj[u][i];
    build(c.v);
    bp[u][i] = bs[u][i] = bs[c.v][1] + c.w;
    dp[u][i] = ds[u][i] = ds[c.v][1];
  }
  for (int i = 1; i <= cc[u]; ++i) 
    dp[u][i] = max({dp[u][i], dp[u][i-1], bp[u][i] + bp[u][i-1]}),
    bp[u][i] = max(bp[u][i], bp[u][i-1]);
  for (int i = cc[u]; i; --i)
    ds[u][i] = max({ds[u][i], ds[u][i+1], bs[u][i] + bs[u][i+1]}),
    bs[u][i] = max(bs[u][i], bs[u][i+1]);
}
void dfs(int u = 0, ll par_longest = 0, ll par_diameter = 0) {
  for (int i = 1; i <= cc[u]; ++i) {
    auto c = adj[u][i];
    ll longest = max(bp[u][i-1], bs[u][i+1]);
    ll diameter = max({dp[u][i-1], ds[u][i+1], bp[u][i-1] + bs[u][i+1]});
    diameter = max({diameter, longest + par_longest, par_diameter});
    res = min(res, abs(diameter - ds[c.v][1]));
    dfs(c.v, max(longest, par_longest) + c.w, diameter);
  }
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  while (cin >> n) {
    if (n == 0) break;
    for (int u = 0; u < n; ++u)
      adj[u].clear(), adj[u].emplace_back();
    res = llinf;
    for (int u = 1, p, w; u <= n-1; ++u) 
      cin >> p >> w, p--,
      adj[p].emplace_back(u, w);
    for (int u = 0; u < n; ++u) 
      adj[u].emplace_back(),
      bp[u].assign(adj[u].size(), 0), 
      dp[u] = ds[u] = bs[u] = bp[u],
      cc[u] = adj[u].size() - 2;
    build();
    dfs();
    cout << res << '\n';
  }
	return 0;
}


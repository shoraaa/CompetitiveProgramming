#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
const ll inf = 1e18;
struct Tree {
  int n; ll total = 0;
  int siz[N], dep[N];
  vector<int> adj[N];
  ll csum[N], sum[N], msum = 0;
  void build1(int u) {
    siz[u] = 1; 
    for (int v : adj[u]) {
      adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
      dep[v] = dep[u] + 1; build1(v); siz[u] += siz[v]; 
      csum[u] += csum[v] + siz[v]; 
    }
    for (int v : adj[u]) 
      total += ll(n - siz[v]) * siz[v];
  }
  void build2(int u) {
    sum[u] = csum[u];
    msum = max(msum, sum[u]);
    for (int v : adj[u]) {
      csum[u] -= csum[v] + siz[v];
      siz[u] -= siz[v]; siz[v] += siz[u];
      csum[v] += csum[u] + siz[u];
      build2(v);
      csum[v] -= csum[u] + siz[u];
      siz[v] -= siz[u]; siz[u] += siz[v];
      csum[u] += csum[v] + siz[v];
    }
  }
  void build() {
    for (int i = 0, u, v; i < n-1; ++i)
      cin >> u >> v, u--, v--,
      adj[u].emplace_back(v),
      adj[v].emplace_back(u);
    build1(0); build2(0); msum += n;
  }
  
  ll sum1, sum2, n1, n2;
  vector<ll> pmax[N], smax[N];
  ll dp[N];
  void dfs1(int u) {
    dp[u] = sum[u] * n2;
    int m = adj[u].size();
    vector<ll> val(m + 1);
    for (int i = 1; i <= m; ++i) {
      int v = adj[u][i-1];
      dfs1(v); val[i] = dp[v] + n1*n2;
      pmax[u][i] = max(pmax[u][i-1], val[i]);
      dp[u] = max(dp[u], val[i]);
    }
    for (int i = m; i; --i) 
      smax[u][i] = max(smax[u][i+1], val[i]);
  }
  ll res = 0;
  void dfs2(int u, ll dp_p = 0) {
    res = max(res, sum[u]*n1 + max(dp[u], dp_p));
    int m = adj[u].size();
    for (int i = 1; i <= m; ++i) {
      int v = adj[u][i-1];
      ll dp_u = max({pmax[u][i-1], smax[u][i+1], sum[u] * n2, dp_p});
      dfs2(v, dp_u + n1*n2);
    }
  }
  ll solve(ll sum1, ll sum2, ll n1, ll n2) {
    this->sum1 = sum1, this->sum2 = sum2, this->n1 = n1, this->n2 = n2;
    for (int v = 0; v < n; ++v) {
      int m = adj[v].size();
      pmax[v].resize(m + 1), smax[v].resize(m + 2);
    }
    dfs1(0); dfs2(0);
    return res + n * (sum1 + sum2) + sum1 * n2 + sum2 * n1;
  }
} t[3];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  for (int i = 0; i < 3; ++i)
    cin >> t[i].n;
  for (int i = 0; i < 3; ++i)
    t[i].build();
  ll res = 0;
  for (int i = 0; i < 3; ++i) {
    int x = (i + 1) % 3, y = (i + 2) % 3;
    ll sum1 = t[x].msum, sum2 = t[y].msum, n1 = t[x].n, n2 = t[y].n;
    res = max(res, t[i].solve(sum1, sum2, n1, n2));
  }
  for (int i = 0; i < 3; ++i)
    res += t[i].total;
  cout << res << '\n';
	return 0;
}


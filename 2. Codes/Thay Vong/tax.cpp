#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5, inf = 1e9;
vector<int> adj[N], con[N], vert[N];
int a[N], comp[N], in[N], low[N]; 
ll val[N][201];
int t = 0, cc = 0; stack<int> st;
void build(int u) {
  in[u] = low[u] = ++t;
  st.emplace(u);
  for (int v : adj[u])
    if (in[v]) low[u] = min(low[u], in[v]);
    else build(v), low[u] = min(low[u], low[v]);
  if (low[u] == in[u]) {
    int v;
    do {
      v = st.top(); st.pop();
      comp[v] = cc, vert[cc].emplace_back(v);
      in[v] = low[v] = inf;
    } while (v != u);
    cc++;
  }
}
ll dp[N][201];
ll call(int u, int k) {
  if (~dp[u][k]) return dp[u][k];
  ll res = val[u][k];
  for (int v : con[u]) for (int i = 0; i <= k; ++i)  
    res = max(res, call(v, k-i) + val[u][i]);
  return dp[u][k] = res;
}
int n, m, k;
void solve() {
  cin >> n >> m >> k;
  for (int v = 0; v < n; ++v)
    cin >> a[v];
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v);
  for (int v = 0; v < n; ++v) 
    if (!in[v]) build(v);
    
  for (int c = 0; c < cc; ++c) {
    sort(vert[c].begin(), vert[c].end(), [](int u, int v) {
      return a[u] < a[v];
    });
    vector<int> vals;
    for (int v : vert[c]) vals.emplace_back(a[v]);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = vert[c].size(); 
    for (int i = 0, j = 0; i < vals.size(); ++i) {
      while (j < m && a[vert[c][j]] < vals[i]) j++;
      if (j <= k)
        val[c][j] = (m - j) * vals[i];
    } 
    for (int i = 1; i <= k; ++i)
      val[c][i] = max(val[c][i-1], val[c][i]);
  }
    
  for (int u = 0; u < n; ++u) for (int v : adj[u]) 
    if (comp[u] != comp[v]) con[comp[u]].emplace_back(comp[v]);
  for (int c = 0; c < cc; ++c)
    sort(con[c].begin(), con[c].end()),
    con[c].erase(unique(con[c].begin(), con[c].end()), con[c].end());
  memset(dp, -1, sizeof(dp));
  ll res = 0;
  for (int v = 0; v < cc; ++v)
    res = max(res, call(v, k));
	cout << res << '\n';
	for (int v = 0; v < n; ++v) 
    adj[v].clear(), con[v].clear(), vert[v].clear();
	memset(in, 0, sizeof(in));
  memset(low, 0, sizeof(low));
  memset(val, 0, sizeof(val));
  t = 0, cc = 0;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("tax.inp", "r"))
    freopen("tax.inp", "r", stdin),
    freopen("tax.out", "w", stdout);
  int T;
  cin >> T;
  while (T--)
    solve();
}


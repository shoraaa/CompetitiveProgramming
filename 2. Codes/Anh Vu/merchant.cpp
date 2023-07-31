#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 100 + 5, K = 1000 + 5; ll inf;
ll buy[N][K], sell[N][K], a[N][N], b[N][N], d[N][N];
int n, m, k;
int check(ll x) {
  memset(d, -0x3f, sizeof(d));
  for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v)
    if (u != v && b[u][v] != inf) d[u][v] = a[u][v] - x * b[u][v]; 
  for (int t = 0; t < n; ++t) for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v)
    if (d[u][t] + d[t][v] > d[u][v]) d[u][v] = d[u][t] + d[t][v];
  for (int u = 0; u < n; ++u)
    if (d[u][u] >= 0) return 1;
  return 0;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < k; ++j)
      cin >> buy[i][j] >> sell[i][j];
  memset(b, 0x3f, sizeof(b)); inf = b[0][0];
  for (int u = 0; u < n; ++u) b[u][u] = 0;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--, b[u][v] = w;
  for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) if (u != v)
    for (int i = 0; i < k; ++i) if (~buy[u][i] && ~sell[v][i]) 
      a[u][v] = max(a[u][v], sell[v][i] - buy[u][i]);
  for (int t = 0; t < n; ++t) for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v)
    b[u][v] = min(b[u][v], b[u][t] + b[t][v]);
  ll lo = 0, hi = 1e9, mid, ans = 0;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid)) 
      ans = mid, lo = mid + 1;
    else
      hi = mid - 1;
  }
  cout << ans;
	return 0;
}
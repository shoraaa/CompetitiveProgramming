#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int a[N], cnt[N][201];
vector<int> pos[201];
int n;
int solve(int u, int e) {
  int m = pos[u].size(), res = 0, cur_max = -1e9;
  for (int i = 0; i < m; ++i) {
    int r = pos[u][i];
    // m-i + cnt[r-1][e] + (j+1-cnt[l][e])
    int j = m-i-1;
    if (j < i) 
      res = max(res, j+1 + m-i + cnt[r-1][e] - cnt[pos[u][j]][e]);
    // for (int j = i; ~j; --j) {
      // int l = pos[u][j];
      // res = max(res, j+1 + m-i + cnt[r-1][e] - cnt[l][e]);
    // }
  }
  return res;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("tpalin.inp", "r"))
    freopen("tpalin.inp", "r", stdin),
    freopen("tpalin.out", "w", stdout);
  int T;
  cin >> T;
  while (T--) {
    cin >> n; int mx = 0;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; ++i) {
      cin >> a[i], mx = max(mx, a[i]);
      pos[a[i]].emplace_back(i);
      for (int v = 1; v <= 200; ++v)
        cnt[i][v] = cnt[i-1][v];
      cnt[i][a[i]]++;
    }
    int res = 0;
    for (int u = 1; u <= mx; ++u) {
      res = max(res, cnt[n][u]);
      for (int e = 1; e <= mx; ++e)
        res = max(res, solve(u, e));
    }
    cout << res << '\n';
    for (int v = 1; v <= mx; ++v)
      pos[v].clear();
  }
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 5;
int a[N][N], vis[N][N];
int n, m;
int check(int r, int c, int v) {
  return 0 <= r && r < n && 0 <= c && c < m && !vis[r][c] && a[r][c] <= v;
}
int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
void dfs(int r, int c) {
  vis[r][c] = 1; 
  for (int d = 0; d < 4; ++d) 
    if (check(r + dr[d], c + dc[d], a[r][c]))
      dfs(r + dr[d], c + dc[d]);
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("selecrect.inp", "r"))
    freopen("selecrect.inp", "r", stdin),
    freopen("selecrect.out", "w", stdout);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    vector<pair<int, int>> pos;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
      cin >> a[i][j], vis[i][j] = 0, pos.emplace_back(i, j);
    sort(pos.begin(), pos.end(), [&](pair<int, int>& u, pair<int, int>& v) {
      return a[u.first][u.second] > a[v.first][v.second];
    });
    int res = 0;
    for (auto& p : pos) if (!vis[p.first][p.second]) 
      dfs(p.first, p.second), res++;
    cout << res << '\n';
  }
	return 0;
}


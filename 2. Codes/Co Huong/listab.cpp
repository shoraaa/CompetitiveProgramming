#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
int inside(int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < m;
}

vector<vector<int>> a, dp;

int call(int i, int j) {
  if (dp[i][j]) return dp[i][j];
  dp[i][j] = 1;
  for (int d = 0; d < 4; ++d) {
    int x = i + dr[d], y = j + dc[d];
    if (inside(x, y) && a[x][y] < a[i][j])
      dp[i][j] = max(dp[i][j], call(x, y) + 1);
  }
  return dp[i][j];
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("listab.inp", "r"))
    freopen("listab.inp", "r", stdin),
    freopen("listab.out", "w", stdout);
    
  cin >> n >> m; a = vector<vector<int>>(n, vector<int>(m)), dp = a;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    cin >> a[i][j];
  int res = 1;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) 
    res = max(res, call(i, j));
  cout << res;
	return 0;
}


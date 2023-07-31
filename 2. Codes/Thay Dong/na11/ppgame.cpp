#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 365;
int dp[N][N][N][2];
string s[N];
int n, m, M;

void add(int& x, const int y) {
  x += y; if (x >= M) x -= M;
}

int dr[4] = {0, 1, 0, -1}, dc[4] = {1, 0, -1, 0};
int inside(int r, int c) {
  return 0 <= r && r < n && 0 <= c && c < m;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> M;
  for (int i = 0; i < n; ++i) 
    cin >> s[i];
  dp[0][0][n - 1][s[0][0] != s[n - 1][m - 1]] = 1;
  
  int res = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {

    if (i + j + 1 >= (n + m) / 2) {
      if (i + j + 1 == (n + m) / 2) {
        if ((n + m - 1) % 2 == 1) {
          add(res, dp[i][j][i][0]),
          add(res, dp[i][j][i][1]);
        } else {
          if (i + 1 < n)
            add(res, dp[i][j][i + 1][0]),
            add(res, dp[i][j][i + 1][1]);
          if (j + 1 < m)
            add(res, dp[i][j][i][0]),
            add(res, dp[i][j][i][1]);
        }
      }
      continue;
    }
    
    for (int r = n - 1; ~r; --r) {
      if (!dp[i][j][r][0] && !dp[i][j][r][1]) continue;
      // i == n-1 - r + m-1 - c
      // c = n-1-r+m-1-x-y
      int c = n-1-r+m-1-i-j;
      for (int d1 = 0; d1 < 2; ++d1) {
        int x = i + dr[d1], y = j + dc[d1];
        if (!inside(x, y)) continue;
        for (int d2 = 2; d2 < 4; ++d2) {
          int u = r + dr[d2], v = c + dc[d2];
          if (!inside(u, v)) continue;
          
          if (s[x][y] == s[u][v])
            add(dp[x][y][u][0], dp[i][j][r][0]),
            add(dp[x][y][u][1], dp[i][j][r][1]);
          else
            add(dp[x][y][u][1], dp[i][j][r][0]);
        }
      }
    }
  }
  cout << res;
	return 0;
}


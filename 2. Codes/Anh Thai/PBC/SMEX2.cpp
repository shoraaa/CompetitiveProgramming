#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5005, M = 1e9 + 7;
int dp[N][N], f[N][N], last[N][N], pre[N][N], a[N];
int n;

inline int sum(int x, int y) { x += y; if (x >= M) x -= M; return x; }
inline int dif(int x, int y) { x -= y; if (x < 0) x += M; return x; }

inline int sum(int l, int r, int x, int y) {
  l++, r++, x++, y++; if (l > r || x > y) return 0;
  return dif(f[r][y], sum(f[l-1][y], dif(f[r][x-1], f[l-1][x-1])));  
}
inline void update(int x, int y) {
  x++, y++;
  f[x][y] = sum(f[x-1][y], dif(f[x][y-1], dif(f[x-1][y-1], dp[x-1][y-1])));
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], a[i]++;
  for (int i = 1; i <= n; ++i) pre[i][0] = i;
  
  dp[0][0] = 1; 
  for (int j = 0; j <= n; ++j) update(0, j);
  
  for (int i = 1; i <= n; ++i) for (int j = 0; j <= n; ++j) {
    if (j) {
      last[i][j] = a[i] == j ? i : last[i - 1][j];
      pre[i][j] = min(pre[i][j - 1], last[i][j]);
      dp[i][j] = sum(last[i][j], pre[i][j - 1] - 1, 0, j);
    }
    update(i, j);
  }
  
  int res = 0;
  for (int j = 1; j <= n; ++j) 
    res = sum(res, dp[n][j]);
  cout << res;
	return 0;
}


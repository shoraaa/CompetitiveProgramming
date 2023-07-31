#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 50 + 5, M = 1e9 + 9;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
int mul(ll x, ll y) {
  return x * y % M;
}
int dp[N][N][N*N * 2][2];
int n, C;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; C = n*n;
  dp[0][0][0 + C][0] = 1;
  for (int i = 0; i < n; ++i) for (int j = 0; j <= n; ++j) {
    for (int k = -n*n + C; k <= n*n + C; ++k) {
      // affected position
      add(dp[i][j+1][k-(i+1)][1], dp[i][j][k][0]);
      // unaffected position
      add(dp[i][j][k][1], mul(dp[i][j][k][0], j));
      
      // contributed value
      if (j) add(dp[i+1][j-1][k+(i+1)][0], mul(dp[i][j][k][1], j));
      // uncontributed value
      add(dp[i+1][j][k][0], dp[i][j][k][1]);
    }
  }
  int res = 0;
  for (int x = 0; x < n * n; ++x)
    add(res, mul(dp[n][0][x + C][0], x + 1));
  cout << res;
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e3 + 5, M = 1e9 + 7;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
void sub(int& x, int y) {
  x -= y; if (x < 0) x += M;
}
int mul(ll x, ll y) {
  return x * y % M;
}
int dp[2][N], sum[2][N];
int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m, m -= n;
  if (m < 0) 
    return cout << 0, 0;
  dp[1][0] = 1;
  for (int i = 0; i <= m; i += n)
    dp[0][i] = 1;
  for (int i = 1, j = 1; j <= m; ++j) {
    dp[1][j] += dp[0][j - n];
    if (j >= n - 1) dp[1][j] += dp[1][j - n + 1];
  }
  for (int i = 2; i <= n; ++i) for (int j = 1; j <= m; ++j) {
    int c = i&1, p = c^1, val = dp[p][j];
    if (j >= n-(i-1)) sub(val, dp[p][j+i-1-n]);
    dp[c][j] = sum[c][j] = 0;
    add(val, sum[p][j]);
   
    if (i < n && j >= n-i) add(dp[c][j], dp[c][j + i - n]);
    add(dp[c][j], val), sum[c][j] = sum[p][j];
   
    int k = i-1; 
    if (j >= n - k) 
      add(dp[c][j], mul(dp[p][j + k - n], i - k + 1)),
      add(sum[c][j], dp[p][j + k - n]);
  }
  cout << dp[n & 1][m]; 
	return 0;
}

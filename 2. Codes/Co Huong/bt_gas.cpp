#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5000 + 5, inf = 1e9;
int dp[N][N];
int a[N];
int n, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  memset(dp, 0x3f, sizeof(dp));
  for (int j = 0; j <= k; ++j) dp[0][j] = a[0] * j;
  for (int i = 1; i <= n; ++i) for (int j = 0; j <= min(k, n-i); ++j) {
    if (i > 0) dp[i][j] = dp[i-1][j+1];
    if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + a[i]);
  }
  cout << dp[n][0];
	return 0;
}


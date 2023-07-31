#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 105;

int dp[N][N], a[N];
int n, k;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    // dp[i][j] = xet i thang dau chia lam j nhom
    // dp[i][j] = dp[i - 1][j] + abs(a[i] - a[i-1]), dp[i - 1][j - 1]
    memset(dp, 0x3f, sizeof(dp));
    dp[1][1] = 0;
    for (int i = 2; i <= n; ++i) {
      for (int j = 1; j <= k; ++j) {
        dp[i][j] = min(dp[i - 1][j] + abs(a[i] - a[i - 1]), dp[i - 1][j - 1]);
      }
    }
    cout << dp[n][k] << '\n';
  }
	return 0;
}


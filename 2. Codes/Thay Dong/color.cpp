#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, inf = 1e9;
int a[N];
pair<int, int> dp[N][105];
#define fi first
#define se second
int n, k;

void cmax(pair<int, int>& x, pair<int, int> y) {
  if (y.fi < x.fi) x = y;
  else if (y.fi == x.fi && y.se > x.se) x = y;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= k; ++j) dp[i][j] = {inf, 0};
  dp[0][0] = {0, 0};
  for (int i = 0; i < n; ++i) for (int j = 0; j <= k; ++j) {
    if (a[i] == 0) {
      if (j != 0 || dp[i][j].se != 0)
        cmax(dp[i + 1][max(0, j - 1)], {dp[i][j].fi, max(0, dp[i][j].se - 1)});
      if (j == 0 && dp[i][j].se == 0) 
        cmax(dp[i + 1][k - 1], {dp[i][j].fi + 1, 0}),
        cmax(dp[i + 1][0], {dp[i][j].fi + 1, k - 1});
    } else if (a[i] == 1) {
      if (j == 0) cmax(dp[i + 1][k - 1], {dp[i][j].fi + 1, max(0, dp[i][j].se - 1)});
      else cmax(dp[i + 1][j - 1], {dp[i][j].fi, max(0, dp[i][j].se - 1)});
    } else if (a[i] == 2) {
      if (dp[i][j].se == 0) cmax(dp[i + 1][max(0, j - 1)], {dp[i][j].fi + 1, k - 1});
      else cmax(dp[i + 1][max(0, j - 1)], {dp[i][j].fi, dp[i][j].se - 1});
    }
  }
  int res = inf;
  for (int j = 0; j <= k; ++j)
    res = min(res, dp[n][j].fi);
  cout << res;
	return 0;
}



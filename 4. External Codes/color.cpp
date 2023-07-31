#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, inf = 1e9;
int a[N];
pair<int, int> dp[N][2];
#define fi first
#define se second
int n, k;

void cmax(pair<int, int>& x, pair<int, int> y) {
  if (y.fi < x.fi) x = y;
  else if (y.fi == x.fi && y.se < x.se) x = y;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= 1; ++j) dp[i][j] = {inf, -inf};
  dp[0][0] = dp[0][1] = {0, inf};
  for (int i = 0; i < n; ++i) for (int j = 0; j <= 1; ++j) {
    if (dp[i][j].fi == inf) continue;
    //cerr << i << ' ' << j << ' ' << dp[i][j].fi << ' ' << dp[i][j].se << '\n';
    if (a[i] == 0) {
      if (dp[i][j].se < k) cmax(dp[i + 1][j], {dp[i][j].fi, dp[i][j].se + 1});
      else cmax(dp[i + 1][0], {dp[i][j].fi + 1, 1}),
           cmax(dp[i + 1][1], {dp[i][j].fi + 1, 1}); 
    } else {
      if (a[i] == j+1 && dp[i][j].se < k) cmax(dp[i + 1][j], {dp[i][j].fi, dp[i][j].se + 1});
      else if (a[i] != j+1) {
        int p = min(n, max(i + 1, i - dp[i][j].se + k));
        if (p > i) cmax(dp[p][a[i] - 1], {dp[i][j].fi + 1, p - i});
      }
      else cmax(dp[i + 1][a[i] - 1], {dp[i][j].fi + 1, 1});
    } 
  }
  int res = inf;
  for (int j = 0; j <= 1; ++j)
    res = min(res, dp[n][j].fi);
  cout << res;
	return 0;
}

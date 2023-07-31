#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e4 + 5, inf = 1e9;
// dp[i][j][k] = v la xet hop i, thong 1 la j thung 2 la k thi so thung it nhat la v
// dp[i][j] = {v, k}
using ii = pair<int, int>;
#define fi first
#define se second
ii dp[N][5005];
int a[N]; int n, L;

void cmin(ii& x, const ii y) {
  return x = min(x, y), void();
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("binpack.inp", "r"))
    freopen("binpack.inp", "r", stdin),
    freopen("binpack.out", "w", stdout);
  cin >> L >> n;
  assert(n < N && L <= 5000);
  for (int i = 0; i < n; ++i) 
    cin >> a[i];
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= L; ++j) dp[i][j] = {inf, 0};
  dp[0][0] = {1, L};
  for (int i = 0; i < n; ++i) for (int j = 0; j <= L; ++j) if (dp[i][j].fi != inf) {
    // bo vao thung 1
    if (j + a[i] <= L) cmin(dp[i + 1][j + a[i]], dp[i][j]);
    else cmin(dp[i + 1][a[i]], ii(dp[i][j].fi + 1, dp[i][j].se));
    // bo vao thung 2
    if (dp[i][j].se + a[i] <= L) cmin(dp[i + 1][j], ii(dp[i][j].fi, dp[i][j].se + a[i]));
    else cmin(dp[i + 1][j], ii(dp[i][j].fi + 1, a[i]));
  }
  int res = inf;
  for (int j = 0; j <= L; ++j)   
    res = min(res, dp[n][j].fi);
  cout << res;
	return 0;
}


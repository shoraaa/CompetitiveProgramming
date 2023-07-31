#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005;
int dp[N][N];
pair<int, int> a[N];
#define fi first
#define se second
int n, d;

int cmax(int& x, int y) {
  return x < y ? x = y, 1 : 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("advent.inp", "r"))
    freopen("advent.inp", "r", stdin),
    freopen("advent.out", "w", stdout);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i].fi >> a[i].se;
  cin >> d;
  sort(a, a + n, [&](pair<int, int>& u, pair<int, int>& v) {
    return u.fi + u.se < v.fi + v.se;
  });
  memset(dp, -0x3f, sizeof(dp));
  dp[0][0] = 0;
  for (int i = 0; i < n; ++i)
    dp[0][0] += a[i].fi;
  for (int i = 0; i < n; ++i) for (int j = 0; j <= i; ++j) {
    if (dp[i][j] + a[i].se >= d) 
      cmax(dp[i + 1][j + 1], dp[i][j] - a[i].fi);
    cmax(dp[i + 1][j], dp[i][j]);
  }
  for (int i = n; i; --i) if (dp[n][i] >= 0)
    return cout << i, 0;
  cout << 0;
	return 0;
}


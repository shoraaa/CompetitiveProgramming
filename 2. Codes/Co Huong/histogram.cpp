#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 16; 
int a[N], dp[1 << N][N], cnt[1 << N][N];
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("histogram.inp", "r"))
    freopen("histogram.inp", "r", stdin),
    freopen("histogram.out", "w", stdout);
    
  while (cin >> n) {
    if (n == 0) break;
    memset(dp, 0, sizeof(dp));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; ++i)
      cin >> a[i], dp[1 << i][i] = a[i], cnt[1 << i][i] = 1;
    for (int msk = 1; msk < 1 << n; ++msk) {

      for (int i = 0; i < n; ++i) if (msk >> i & 1) {
        if (!dp[msk][i]) continue;
        for (int j = 0; j < n; ++j) if (!(msk >> j & 1)) {
          if (dp[msk][i] + abs(a[i] - a[j]) > dp[msk | (1 << j)][j])
            dp[msk | (1 << j)][j] = dp[msk][i] + abs(a[i] - a[j]),
            cnt[msk | (1 << j)][j] = cnt[msk][i];
          else if (dp[msk][i] + abs(a[i] - a[j]) == dp[msk | (1 << j)][j])
            cnt[msk | (1 << j)][j] += cnt[msk][i];
          }
       }
       
    }
    int res = 0, ans = 0;
    for (int i = 0; i < n; ++i) 
      if (dp[(1 << n) - 1][i] + a[i] + n * 2 > res)
        res = dp[(1 << n) - 1][i] + a[i] + n * 2, 
        ans = cnt[(1 << n) - 1][i];
      else if (dp[(1 << n) - 1][i] + a[i] + n * 2 == res)
        ans += cnt[(1 << n) - 1][i];
    cout << res << ' ' << ans << '\n';
  }
	return 0;
}


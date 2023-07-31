#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005;
int a[N], dp[N][N];
int n, p, q;

int check(int w) {
  // dp[i][j] = xet den i dung j may loai p, so may loai q phai dung it nhat la?
  memset(dp, 0x3f, sizeof(dp));
  for (int i = 0; i <= min(n, p); ++i) dp[n][i] = 0;
  for (int i = n - 1; ~i; --i) {
    int i1 = upper_bound(a, a + n, a[i] + w - 1) - a,
        i2 = upper_bound(a, a + n, a[i] + w*2 - 1) - a;
    for (int j = 0; j <= min(n, p); ++j)
      dp[i][j] = min(dp[i1][j + 1], dp[i2][j] + 1);
  }
  for (int i = 0; i <= min(n, p); ++i) if (dp[0][i] <= q) return 1;
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("watching.inp", "r"))
    freopen("watching.inp", "r", stdin),
    freopen("watching.out", "w", stdout);
    
  cin >> n >> p >> q;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  sort(a, a + n);
  int lo = 1, hi = 1e9, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid))
      ans = mid,
      hi = mid - 1;
    else
      lo = mid + 1;
  }
  cout << ans;
	return 0;
}


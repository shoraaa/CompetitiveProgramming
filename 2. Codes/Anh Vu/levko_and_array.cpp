#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2000 + 5;
int n, k;
int a[N], dp[N];
int ok(int i, int j, ll x) {
  if (x == 0) return a[i] == a[j];
  return (abs(a[i] - a[j]) - 1) / x <= (i - j - 1);
}
int check(ll x) {
  dp[0] = 0;
  int res = n-1;
  for (int i = 1; i < n; ++i) {
    dp[i] = i;
    for (int j = i-1; ~j; --j) if (ok(i, j, x)) 
      dp[i] = min(dp[i], dp[j] + i - j - 1);
    res = min(res, dp[i] + n - i - 1);
  }
  return res <= k;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  ll lo = 0, hi = 2e9, mid, ans = -1;
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


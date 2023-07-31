#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int dp[1 << 18][51];
int n;
int a[18][2];
int call(int msk, int last) {
  int pos = __builtin_popcount(msk);
  if (pos == n) return 0;
  if (dp[msk][last] != -1) return dp[msk][last];
  int res = 1e9, after = 0;
  for (int i = n-1; ~i; --i) if (!(msk >> i & 1)) {
    int val = a[i][abs(i - pos) & 1];
    if (val < last) continue;
    res = min(res, call(msk | (1 << i), val) + abs(i + after - pos));
  } else after++;
  return dp[msk][last] = res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i][0];
  for (int i = 0; i < n; ++i)
    cin >> a[i][1];
  memset(dp, -1, sizeof(dp));
  int res = call(0, 0);
  cout << (res == 1e9 ? -1 : res);
	return 0;
}


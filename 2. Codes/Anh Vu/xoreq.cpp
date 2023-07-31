#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = (1 << 20) + 5, M = 1e9 + 7;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
int mul(ll x, ll y) {
  return x * y % M;
}
int pw(ll x, ll k) {
  if (k < 0) return 0;
  ll res = 1;
  for (; k; k >>= 1, x = mul(x, x))
    if (k & 1) res = mul(res, x);
  return res;
}
int a[N], f[N], cnt[N], dp[N], sum_dp[N], last[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);             
  cin >> n; 
  for (int i = 1; i <= n; ++i)
    cin >> a[i], f[i] = f[i-1] ^ a[i],
    cnt[i] = cnt[i-1] + (f[i] == 0);
  int prefix_dp = pw(2, cnt[n] - 1); 
  dp[0] = sum_dp[0] = 1;
  for (int i = 1; i <= n; ++i) if (f[i]) {
      dp[i] = dp[last[f[i]]],
      add(dp[i], mul(sum_dp[f[i]], cnt[i-1] - cnt[last[f[i]]])),
      add(sum_dp[f[i]], dp[i]),
      add(prefix_dp, dp[i]);
    last[f[i]] = i;
  }
  cout << dp[n] + (f[n] == 0 ? prefix_dp : 0);
	return 0;
}


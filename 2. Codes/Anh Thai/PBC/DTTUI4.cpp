#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 105, M = 998244353;
int n, s, K;

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

int pw1[N];

int fac[N], inv[N];
inline ll C(int n, int k) {
  return 1LL * fac[n] * inv[k] % M * inv[n-k] % M;
}

vector<int> dp[N];
int c[N], v[N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> s >> K;
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= K; ++i)
    fac[i] = 1LL * fac[i-1] * i % M,
    inv[i] = pw(fac[i], M - 2);
  for (int i = 0; i < n; ++i)
    cin >> c[i] >> v[i];
  for (int i = 0; i <= s; ++i)
    dp[i] = vector<int>(K + 1); 
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    pw1[0] = 1;
    for (int j = 1; j <= K; ++j) 
      pw1[j] = 1LL * pw1[j-1] * v[i] % M;
    for (int j = s; ~j; --j) if (j >= c[i]) {
      // cap nhat tu dp[j-a[i]] len dp[j]
      // dp[j-a[i]] = {V0, V1, V2, V3, .., Vk}
      ll val = v[i], w = c[i];
      for (int k = 0; k <= K; ++k) { 
        for (int i = 0; i <= k; ++i) {
          dp[j][k] += dp[j - w][i] * C(k, i) % M * pw1[k-i] % M;
          if (dp[j][k] >= M) dp[j][k] -= M;
        }
      }
    }
  }
  int res = 0;
  for (int i = 0; i <= s; ++i) {
    res += dp[i][K];
    if (res >= M) res -= M;
  }
  cout << res;
}
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
const int N = 5e5 + 5, M = 1e9 + 7;
void add(int& x, int y) { x += y; if (x >= M) x -= M; }
void sub(int& x, int y) { x -= y; if (x < 0) x += M; }
int dif(int x, int y) { x -= y; if (x < 0) x += M; return x; }
ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

int fac[N], inv[N], f[N];
ll C(int n, int k) {
  return 1LL * fac[n] * inv[k] % M * inv[n-k] % M;
}


namespace task1 {
  const int N = 5e5 + 5;
  int dp[N][105];
  int solve() {
    if (m == 1) return 1;
    if (m == 2) return dif(pw(2, n), 1);
    for (int i = 1; i < n; ++i)
      dp[2][i] = C(n, i);
    for (int j = 2; j <= m; ++j) for (int k = 1; k < n; ++k) 
      for (int t = 1; t <= n-k; ++t) add(dp[j + 1][t], dp[j][k] * C(n - k, t) % M);
    
    int res = 0;
    for (int i = 1; i < n; ++i) 
      add(res, dp[m][i]);
    return res;
  }
};

namespace task2 {
  const int N = 5005;
  int dp[N];
  int solve() {
    // dp[j] = so cach dien bang n x j = (tong so cach) - (so cach deo thoa man)
    dp[1] = 1;
    for (int j = 2; j <= m; ++j) {
      dp[j] = pw(f[j], n);
      for (int k = j; k >= 2; --k)
        sub(dp[j], pw(f[k - 1], n) * dp[j - k + 1] % M);
    }
    return dp[m];
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  fac[0] = inv[0] = 1;
  for (int i = 1; i < N; ++i)
    fac[i] = 1LL * fac[i - 1] * i % M,
    inv[i] = pw(fac[i], M - 2);
  f[0] = f[1] = 1;
  for (int i = 2; i < N; ++i)
    add(f[i], f[i-1]), add(f[i], f[i-2]);
  
  cin >> m >> n;
  if (m > 5000) cout << task1::solve();
  else cout << task2::solve();
	return 0;
}


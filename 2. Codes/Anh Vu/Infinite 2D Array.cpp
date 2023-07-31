#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e6 + 5, M = 1e9 + 7;

void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}

ll fib[N], fac[N], inv[N];
ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}
ll C(ll n, ll k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * inv[k] % M * inv[n-k] % M;
}
int n, m;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  fib[0] = 0, fib[1] = 1;
  for (int i = 2; i <= max(n, m); ++i)
    fib[i] = (fib[i-1] + fib[i-2]) % M;
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= n + m; ++i)
    fac[i] = fac[i-1] * i % M,
    inv[i] = pw(fac[i], M-2);
  int res = 0; 
  for (int i = 1; i <= n; ++i)
    add(res, C(n+m-i-1, n-i) * fib[i] % M);
  for (int i = 1; i <= m; ++i)
    add(res, C(n+m-i-1, m-i) * fib[i] % M);
  cout << res;
	return 0;
}


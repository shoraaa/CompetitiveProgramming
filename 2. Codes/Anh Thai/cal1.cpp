#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e6 + 3;
ll fac[M+1], inv[M+1];

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * inv[k] % M * inv[n - k] % M;
}

ll lucas(ll n, ll m) {
  if (m == 0) return 1;
  ll ni = n % M, mi = m % M;
  return lucas(n / M, m / M) * C(ni, mi) % M;
}

ll a, b, n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= M; ++i)
    fac[i] = fac[i-1] * i % M,
    inv[i] = pw(fac[i], M-2);
    
  int T; cin >> T;
  while (T--) {
    cin >> a >> b >> n >> m;
    // di n+m-2 buoc, n-1 buoc sang, m-1 buoc xuong
    // -> *a^(n-1), b^(m-1)
    ll res = lucas(n+m-2, n-1);
    res = res * pw(a, n-1) % M;
    res = res * pw(b, m-1) % M;
    cout << res << '\n';
  }
	return 0;
}


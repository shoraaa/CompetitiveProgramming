#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e6 + 5, M = 1e9 + 7;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
void sub(int& x, int y) {
  x -= y; if (x < 0) x += M;
}
int fac[N], inv[N];
int pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}
int C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return ll(fac[n]) * inv[k] % M * inv[n-k] % M;
}
ll D(int n, int k) {
  return C(n + k - 1, n);
}
int n, m, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> k, m++, k++;
  fac[0] = inv[0] = 1;
  for (int i = 1; i < N; ++i)
    fac[i] = ll(fac[i-1]) * i % M,
    inv[i] = pw(fac[i], M-2);
  int res = 0;
  for (int i = 0; i <= n; ++i) {
    if (n-i*k < 0) break;
    int cur = D(n - i * k, m) * C(m, i) % M;
    if (i & 1) sub(res, cur);
    else add(res, cur);
  }
  cout << res;
	return 0;
}


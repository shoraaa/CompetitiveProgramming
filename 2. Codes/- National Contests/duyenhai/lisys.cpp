#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5, M = 1e9 + 7;
void add(int& x, int y) {
	x += y; if (x >= M) x -= M;
}
void sub(int& x, int y) {
	x -= y; if (x < 0) x += M;
}
int mul(ll x, ll y) {
	return x * y % M;
}
int pw(ll x, ll k) {
	ll res = 1;
	for (; k; k >>= 1, x = mul(x, x)) 
		if (k & 1) res = mul(res, x);
	return res;
}
int fac[N];
int C(int n, int k) {
  if (n < k) return 0;
  return ll(fac[n]) * pw(fac[n-k], M-2) % M * pw(fac[k], M-2) % M; 
}
int n, m = 0, s = 0;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0, x; i < n; ++i) 
    cin >> x,
    m += x == -1,
    s += x == -1 ? 0 : x;
  // tong s + Zdi = 2n-2
  // d1 + d2 + .. + dm = 2n-2-s, 1 <= di < n
  s = 2 * n - 2 - s;
  if (s < m) 
    return cout << 0, 0;
  s -= m, n--;
  fac[0] = 1;
  for (int i = 1; i < N; ++i)
    fac[i] = mul(fac[i-1], i);
  int res = 0;
  for (int i = 0; i <= m; ++i) {
    int cur = mul(C(m, i), C(m+s-i*n-1, m-1));
    if (i & 1) sub(res, cur);
    else add(res, cur);
  }
  cout << res;
	return 0;
}


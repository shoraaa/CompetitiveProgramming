#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, M = 1e9 + 7;
int n, v, position, x, y;

void binary_search() {
  int l = 0;
  int r = n - 1;
  while (l <= r) {
     int m = (l + r + 1) / 2;
     if (m == position)
       return;
     else if (m > position) // a[m] > v
       x++, r = m - 1;
     else // a[m] < v
       y++, l = m + 1;
  }
}
ll fac[N], inv[N];

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

ll C(int n, int k) {
  if (n < k) return 0;
  return fac[n] * inv[k] % M * inv[n - k] % M;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> v;
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= n; ++i)
    fac[i] = fac[i - 1] * i % M,
    inv[i] = pw(fac[i], M - 2);

  int res = 0;
  for (int i = 0; i < n; ++i) {
    position = i; x = y = 0;
    binary_search();
    res += C(v - 1, y) * C(n - v, x) % M * fac[n - x - y - 1] % M * fac[x] % M * fac[y] % M;
    if (res >= M) res -= M;
  }
  cout << res;
	return 0;
}


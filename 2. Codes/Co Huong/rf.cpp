#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1005;
ll a[N], b[N], n, m, M;

ll mul(ll x, ll k) {
  ll res = 0;
  for (; k; k >>= 1, x = (x + x) % M)
    if (k & 1) res = (res + x) % M;
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("rf.inp", "r"))
    freopen("rf.inp", "r", stdin),
    freopen("rf.out", "w", stdout);
  cin >> n >> m >> M;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0; i < m; ++i)
    cin >> b[i];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int g = __gcd(a[i], b[j]);
      a[i] /= g; b[j] /= g;
    }
  }
  ll p = 1, q = 1;
  for (int i = 0; i < n; ++i)
    p = mul(p, a[i]);
  for (int i = 0; i < m; ++i)
    q = mul(q, b[i]);
  cout << p << '\n' << q << '\n';
	return 0;
}


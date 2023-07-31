#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e7 + 5;
int n, m;

void add(int& x, int y) {
  x += y; x %= m;
}
void sub(int& x, int y) {
  x -= y; x %= m; if (x < 0) x += m;
}

void f(ll n, ll&x, ll&y){
  if (n==0) 
    return x = 0, y = 1, void();
  if (n & 1) {
    f(n-1, x, y); swap(x, y);
    y = (y + x) % m;
  } else {
    ll a, b;
    f(n>>1, a, b);
    y = (a * a + b * b) % m;
    x = (a * b + a * (b - a + m)) % m;
  }
}
int fib(ll n) {
  ll x, y;
  f(n, x, y);
  return x;
}
int pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % m)
    if (k & 1) res = res * x % m;
  return res;
}

ll fac[N], inv[N];
ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * inv[k] % m * inv[n - k] % m;
}

ll lucas(ll n, ll k) {
  if (k == 0) return 1;
  ll ni = n % m, ki = k % m;
  return lucas(n / m, k / m) * C(ni, ki) % m;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> n >> m;
    
    fac[0] = 1; int mx = min(n, m - 1);
    for (int i = 1; i <= mx; ++i) 
      fac[i] = fac[i-1] * i % m;
    inv[mx] = pw(fac[mx], m-2);
    for (int i = mx-1; i >= 0; --i)
      inv[i] = inv[i + 1] * (i + 1) % m;
    
    int res = fib(n + 2);
    if (n % 2 == 0) {
      add(res, lucas(n, n / 2));
      sub(res, n / 2 + 1);
    }
    cout << res << '\n';
  }
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5, M = 1e9 + 7;
struct Point {
  ll a, b, c;
} a[N];
int n;


ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M) {
    if (k & 1) {
      res = res * x % M;
    }
  }
  return res;
}


ll eval() {
  ll res = 0;
  sort(a + 1, a + n + 1, [](const Point& u, const Point& v) {
    return u.a < v.a;
  });
  
  ll sum_cj = 0, sum_ajcj = 0, sum_aj = 0;
  for (int i = 1; i <= n; ++i) {
    
    res += a[i].a * sum_cj - sum_ajcj;
    res += a[i].c * (a[i].a * (i - 1) - sum_cj);
    res %= M;
    
    sum_cj += a[i].c;
    sum_aj += a[i].a;
    sum_ajcj += a[i].a * a[i].c;
  }

  sum_cj = sum_aj = sum_ajcj = 0;
  for (int i = n; i; --i) {
    
    res += sum_ajcj - a[i].a * sum_cj;
    res += a[i].c * (sum_cj - a[i].a * (i - 1));
    res %= M;
    
    sum_cj += a[i].c;
    sum_aj += a[i].a;
    sum_ajcj += a[i].a * a[i].c;
  }
  
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("class.inp", "r")) {
    freopen("class.inp", "r", stdin);
    freopen("class.out", "w", stdout);
  }
  
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].a;
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].b;
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].c;
  }
  
  ll res = 0;
  res += eval();
  for (int i = 1; i <= n; ++i) {
    swap(a[i].a, a[i].b);
  }
  res += eval();
  res %= M;
  
  for (int i = 1; i <= n; ++i) {
    swap(a[i].a, a[i].b);
    ll x = a[i].a + a[i].b, y = a[i].a - a[i].b;
    a[i].a = x, a[i].b = y;
  }
  
  ll tmp = eval();
  for (int i = 1; i <= n; ++i) {
    swap(a[i].a, a[i].b);
  }
  tmp += eval();
  tmp %= M;
  tmp = tmp * pw(2, M - 2) % M;
  
  res -= tmp;
  if (res < 0) res += M;
  cout << res;
  
  
	return 0;
}


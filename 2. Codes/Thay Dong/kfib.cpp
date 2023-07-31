#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1.5e6;
const ll inf = 1e18;
int m, A, B;

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
int solve1() {
  if (A == 0 && B == 1)
    return 0;
  for (int i = 1, pre = 0, cur = 1; i < m * 6 + 5; ++i) {
    int nxt = pre + cur;
    if (nxt >= m) nxt -= m;
    if (cur == A && nxt == B)
      return i;
    pre = cur; cur = nxt;
  } 
  return -1;
}
using Tp = pair<int, int>;
int solve() {
  cin >> m >> A >> B;
  int k = sqrt(6LL * m);
  map<Tp, int> mp;
  for (int nxt = B, cur = A, b = 0; b < k; ++b) {
    Tp p = {cur, nxt};
    mp[p] = b;
    int pre = nxt - cur;
    if (pre < 0) pre += m;
    nxt = cur, cur = pre; 
  }

  for (ll a = 0; a < k; ++a) {
    Tp p = {fib(a * k), fib(a * k + 1)};
    
    if (mp.count(p)) 
      return ll(a) * k + mp[p];
  }
  return -1;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) 
    cout << solve() << '\n';
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const int N = 6000 + 5, M = 1e6;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
struct P {
  ll x, y;
  P(int x = 0, int y = 0): x(x), y(y) {}
  bool operator < (const P& p) const {
    if (x == p.x)
      return y < p.y;
    return x < p.x;
  }  
  bool operator != (const P& p) const {
    return x != p.x || y != p.y;
  }
};
struct S {
  P u, v;
  ll a, b, c;
  S(P u, P v): u(u), v(v), a(v.y - u.y), b(u.x - v.x), c(-(a * u.x + b * u.y)) {}
  bool include(P& p) {
    return a * p.x + c == -b * p.y;
  }
};
int intersection(S s, S t, P& p) {
  ll m = s.a * t.b - t.a * s.b;
  p.x = s.b * t.c - t.b * s.c;
  p.y = s.c * t.a - t.c * s.a;
  if (m == 0 || p.x % m != 0 || p.y % m != 0)
    return 0;
  p.x /= m, p.y /= m;
  if (abs(p.x) > M || abs(p.y) > M)
    return 0;
  return 1;
}
vector<P> a; int n;
void reduce(vector<P>& b) {
  if (b.empty()) return;
  int g = rng() % (n - 2) + 2;
  vector<int> good(b.size());
  for (int j = 2; j < n; ++j) if (j != g) {
    S s(a[g], a[j]);
    for (int i = 0; i < b.size(); ++i)
      if (s.include(b[i])) good[i] = 1;
  }
  vector<P> res;
  for (int i = 0; i < b.size(); ++i)
    if (good[i]) res.emplace_back(b[i]);
  res.swap(b);
}
int check(P& p) {
  vector<P> res = a;
  for (P& c : res) {
    c.x -= p.x, c.y -= p.y;
    int g = __gcd(c.x, c.y);
    c.x /= g, c.y /= g;
  }
  sort(res.begin(), res.end());
  for (int i = 0; i < n; i += 2)
    if (res[i] != res[i + 1]) return 0;
  return 1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n; n *= 2;
	for (int i = 0, x, y; i < n; ++i)
	  cin >> x >> y, 
	  a.emplace_back(x, y);
	if (n == 2)
	  return cout << -1, 0;
  // dt di qua (a[0].x, a[0].y) -> (a[1].x, a[1].y)
  vector<P> b;
  S s(a[0], a[1]); P p;
  for (int i = 2; i < n; ++i) for (int j = i+1; j < n; ++j) {
    if (intersection(s, S(a[i], a[j]), p))
      b.emplace_back(p);
  }
  // dt ko di qua 0,1
  for (int i = 2; i < n; ++i) for (int j = i+1; j < n; ++j) {
    if (intersection(S(a[0], a[i]), S(a[1], a[j]), p))
      b.emplace_back(p);
    if (intersection(S(a[1], a[i]), S(a[0], a[j]), p))
      b.emplace_back(p);
  }
  for (P& c : b)
    assert(abs(c.x) <= M),
    assert(abs(c.y) <= M);
  int t = 5;
  while (t--)
    reduce(b);
  for (P& p : b) if (check(p))
    return cout << "Yes\n" << p.x << ' ' << p.y << '\n', 0;
  cout << "No";
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using Tp = long double;
using Pt = pair<Tp, Tp>;
#define x first
#define y second
const int N = 1e3 + 5;
Pt a[N];
int n;
array<Pt, 2> get(Pt& a, Pt& c) {
  Tp midX = (a.x + c.x) / 2;
  Tp midY = (a.y + c.y) / 2;

  Tp Ax = a.x - midX;
  Tp Ay = a.y - midY;
  Tp bX = midX - Ay;
  Tp bY = midY + Ax;
  Pt b(bX, bY);

  Tp cX = (c.x - midX);
  Tp cY = (c.y - midY);
  Tp dX = midX - cY;
  Tp dY = midY + cX;
  Pt d(dX, dY);

  array<Pt, 2> res = {b, d};
  return res;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("square.inp", "r")) 
    freopen("square.inp", "r", stdin),
    freopen("square.out", "w", stdout);
  cin >> n; set<Pt> s;
  for (int i = 0; i < n; ++i)
    cin >> a[i].x >> a[i].y,
    s.insert(a[i]);
  auto d = get(a[0], a[n-1]);
  ll res = 0;
  for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
    auto d = get(a[i], a[j]);
    res += s.count(d[0]) && s.count(d[1]);
  }
  cout << res / 2;
	return 0;
}


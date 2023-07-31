#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct Point {
  ll x, y;
  Point(ll x = 0, ll y = 0): x(x), y(y) {}
  bool operator == (const Point& p) const {
    return x == p.x && y == p.y;
  }
  bool operator < (const Point& p) const {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
};
int ccw(Point& a, Point& b, Point& c) {
  return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}
const int N = 1e4 + 5;
Point a[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  while (cin >> n) {
    if (n == 0) break;
    for (int i = 0; i < n; ++i)
      cin >> a[i].x >> a[i].y;
    sort(a, a + n), n = unique(a, a + n) - a;
    vector<Point> hull;
    for (int i = 0; i < n; ++i) {
      while (hull.size() > 1 && !ccw(hull[hull.size() - 2], hull.back(), a[i]))
        hull.pop_back();
      hull.emplace_back(a[i]);
    }
    int d = hull.size();
    for (int i = n-1; ~i; --i) {
      while (hull.size() > d && !ccw(hull[hull.size() - 2], hull.back(), a[i]))
        hull.pop_back();
      hull.emplace_back(a[i]);
    }
    hull.pop_back();
    cout << hull.size() << '\n';
    for (auto& p : hull)
      cout << p.x << ' ' << p.y << '\n';
  }
	return 0;
}


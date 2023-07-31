#include<bits/stdc++.h> 
using namespace std;
using ll = long long;
using Tp = long double;
struct Point {
  Tp x, y;
  Point operator + (const Point p) { return {x + p.x, y + p.y}; }
  Point operator - (const Point p) { return {x - p.x, y - p.y}; }
  Point operator * (const Tp t) { return {x * t, y * t}; }
  Point operator / (const Tp t) { return {x / t, y / t}; }
  bool operator < (const Point& p) const { return (y < p.y) || (y == p.y && x < p.x); }
};
Tp dot(Point p, Point q) { return p.x * q.x + p.y * q.y; }
Tp cross(Point p, Point q) { return p.x * q.y - p.y * q.x; }
Tp orient(Point a, Point b, Point p) { return cross(b - a, p - a); }
struct Line {
  Point p, v; Tp c;
  Line() = default;
  Line(Point p, Point q): p(p), v(q - p), c(cross(v, p)) {}
  bool onSegment(Point& q) {
    return orient(p, p + v, q) == 0 && dot(p - q, p + v - q) <= 0;
  }
  bool inter(Line& l, Point& out) {
    Tp d = cross(v, l.v);
    if (d == 0) return 0;
    out = l.v * c - v * l.c;
    if ((ll)out.x % (ll)d != 0 || (ll)out.y % (ll)d != 0) return 0;
    out = out / d;
    if (!l.onSegment(out) || !onSegment(out)) return 0;
    return 1;
  }
  ll count() {
    Point q = p + v;
    return __gcd((ll)abs(p.x - q.x), (ll)abs(p.y - q.y)) + 1;
  }
};
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; vector<Line> seg;
  ll res = 0; Tp x, y;
  for (int i = 0; i < n; ++i) {
    Point p, q; Line l;
    cin >> x >> y, p = {x, y};
    cin >> x >> y, q = {x, y};
    l = {p, q};
    seg.emplace_back(l);
    res += l.count();
  }
  set<Point> dup; Point p;
  for (int i = 0; i < n; ++i) {
    set<Point> cur;
    for (int j = 0; j < n; ++j) if (i != j) {
      if (seg[i].inter(seg[j], p)) 
        cur.insert(p), dup.insert(p);
    }
    res -= cur.size();
  }
  cout << res + dup.size();
	return 0;
}
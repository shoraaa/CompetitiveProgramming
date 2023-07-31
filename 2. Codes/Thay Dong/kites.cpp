#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 55, M = 1e9 + 7;
int dp[N][N][N][N];
int n;

struct Point {
  int x, y;
  bool operator < (const Point& p) const {
    return x < p.x;
  }
  friend ostream& operator << (ostream& os, const Point& p) {
    return os << p.x << ',' << p.y;
  }
} a[N], b[N];

struct Line {
  Point p1, p2;
};
 
int onLine(Line l1, Point p) {
    // Check whether p is on the line or not
    if (p.x <= max(l1.p1.x, l1.p2.x) && p.x >= min(l1.p1.x, l1.p2.x)
    && (p.y <= max(l1.p1.y, l1.p2.y) && p.y >= min(l1.p1.y, l1.p2.y)))
      return 1;
    return 0;
}
 
int direction(Point a, Point b, Point c) {
  int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
  if (val == 0) return 0;
  else if (val < 0) return 2;
  return 1;
}
 
int intersect(Line l1, Line l2){

  int dir1 = direction(l1.p1, l1.p2, l2.p1);
  int dir2 = direction(l1.p1, l1.p2, l2.p2);
  int dir3 = direction(l2.p1, l2.p2, l1.p1);
  int dir4 = direction(l2.p1, l2.p2, l1.p2);

  if (dir1 != dir2 && dir3 != dir4) return 1;
  if (dir1 == 0 && onLine(l1, l2.p1)) return 1;
  if (dir2 == 0 && onLine(l1, l2.p2)) return 1;
  if (dir3 == 0 && onLine(l2, l1.p1)) return 1;
  if (dir4 == 0 && onLine(l2, l1.p2)) return 1;

  return 0;
}
 
int inside(const Point& p, const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
  int cnt = 0, tmp = 0;
  
  Line line = {p, {10001, p.y}};
  
  if (intersect(line, {p1, p2})) {
    if (direction(p1, p, p2) == 0) return onLine({p1, p2}, p);
    cnt++; tmp += (p1.y == p.y && p1.x >= p.x) || (p2.y == p.y && p2.x >= p.x);
  }
  
  if (intersect(line, {p2, p3})) {
    if (direction(p2, p, p3) == 0) return onLine({p2, p3}, p);
    cnt++; tmp += (p2.y == p.y && p2.x >= p.x) || (p3.y == p.y && p3.x >= p.x);
  }
  
  if (intersect(line, {p3, p4})) {
    if (direction(p3, p, p4) == 0) return onLine({p3, p4}, p);
    cnt++; tmp += (p3.y == p.y && p3.x >= p.x) || (p4.y == p.y && p4.x >= p.x);
  }
  
  if (intersect(line, {p4, p1})) {
    if (direction(p4, p, p1) == 0) return onLine({p4, p1}, p);
    cnt++; tmp += (p4.y == p.y && p4.x >= p.x) || (p1.y == p.y && p1.x >= p.x);
  }
  
  return (cnt + tmp / 2) & 1;
}

bool on_segment(Point& p, Point& a, Point& b)
{
    auto dxc = p.x - a.x;
    auto dyc = p.y - a.y;
    
    auto dxl = b.x - a.x;
    auto dyl = b.y - a.y;
    
    auto cross = dxc * dyl - dyc * dxl;
    if (cross != 0) return 0;
    if (abs(dxl) >= abs(dyl))
      return dxl > 0 ? a.x <= p.x && p.x <= b.x : b.x <= p.x && p.x <= a.x;
    return dyl > 0 ? a.y <= p.y && p.y <= b.y : b.y <= p.y && p.y <= a.y;
}

int call(int l, int r, int kl, int kr, vector<int>& cur) {
  if (r - l <= 1) return 1;
  if (dp[l][r][kl][kr] != -1) return dp[l][r][kl][kr];
  
  vector<int> nxt; int id = -1;
  for (int i : cur) {
    if (on_segment(b[i], a[l], b[kl])) continue;
    if (on_segment(b[i], a[r], b[kr])) continue;
    if (inside(b[i], a[l], b[kl], b[kr], a[r])) {
      nxt.emplace_back(i); if (id == -1 || b[i].y > b[id].y) id = i;
    }
  }
  
  if (nxt.empty() || nxt.size() != r - l - 1) return dp[l][r][kl][kr] = 0;
  
  int res = 0;

  for (int m = l + 1; m <= r - 1; ++m) {
    res += 1LL * call(l, m, kl, id, nxt) * call(m, r, id, kr, nxt) % M;
    if (res >= M) res -= M;
  }

  return dp[l][r][kl][kr] = res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("kites.inp", "r"))
    freopen("kites.inp", "r", stdin),
    freopen("kites.out", "w", stdout);
  cin >> n; int mx = 0, my = 0;
  for (int i = 1; i <= n; ++i)
    cin >> a[i].x, a[i].y = 0, mx = max(mx, a[i].x);
  sort(a + 1, a + n + 1); 
  for (int i = 1; i <= n - 1; ++i)
    if (a[i].x == a[i + 1].x) return cout << 0, 0;

  for (int i = 1; i <= n; ++i)
    cin >> b[i].x >> b[i].y, mx = max(mx, b[i].x), my = max(my, b[i].y);
  a[0].x = b[0].x = -1, a[n + 1].x = b[n + 1].x = mx + 1, b[0].y = b[n + 1].y = my;
  
  memset(dp, -1, sizeof(dp));
  vector<int> cur(n); iota(cur.begin(), cur.end(), 1);
  cout << call(0, n + 1, 0, n + 1, cur);
	return 0;
}


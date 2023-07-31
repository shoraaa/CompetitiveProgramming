#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int N = 5e4 + 5;
struct H {
  ll x, y, s;
  H(ll x = 0, ll y = 0, ll s = 0): x(x), y(y), s(s) {}
} a[N];

struct R {
  ld bot, top, lef, rig;
  R(ld bot, ld top, ld lef, ld rig): bot(bot), top(top), lef(lef), rig(rig) {}
  int contain(ld x, ld y) {
    return lef <= x && x <= rig && bot <= y && y <= top;
  }
};

int n, k;

#define fi first
#define se second

int check1(vector<pair<ld, ld>>& a, int k) {
  sort(a.begin(), a.end());
  int cnt = 1; ld cur = 1e18;
  for (auto& p : a) {
    if (p.fi <= cur) cur = min(cur, p.se);
    else cnt++, cur = p.se;
  }
  return cnt <= k;
}

ld bot, top, lef, rig;

int check2(vector<R>& rect, int k) {
  if (k == 1) return 0;
  
  if (k == 2) {
    ld x1 = -1e18, y1 = -1e18, x2 = 1e18, y2 = 1e18;
    for (auto& r : rect) 
      x1 = max(x1, r.lef), x2 = min(x2, r.rig),
      y1 = max(y1, r.bot), y2 = min(y2, r.top);
    int cnt = 0;
    for (auto& r : rect) cnt += r.contain(x1, y1) || r.contain(x2, y2);
    if (cnt == rect.size()) return 1;
    swap(y1, y2); cnt = 0;
    for (auto& r : rect) cnt += r.contain(x1, y1) || r.contain(x2, y2);
    return cnt == rect.size();
  } 
  
  vector<ld> cx = {lef, rig}, cy = {bot, top};
  
  for (int msk = 0; msk < 1 << 2; ++msk) {
    ld x = cx[msk >> (0) & 1], y = cy[msk >> (1) & 1];
    vector<R> nxt;
    for (auto& r : rect) if (!r.contain(x, y)) nxt.emplace_back(r);
    if (check2(nxt, k - 1)) return 1;
  }
  
  return 0;
  
}

int check(ld s) {
  vector<R> rect;
  vector<pair<ld, ld>> totx, toty;
  lef = bot = -1e18, top = rig = 1e18;
  for (int i = 0; i < n; ++i) {
    ld t = a[i].s * s, x = a[i].x, y = a[i].y; 
    ld x1 = x-y-t, x2 = x-y+t, y1 = x+y-t, y2 = x+y+t;
    if (x1 > x2) swap(x1, x2); if (y1 > y2) swap(y1, y2);
    rect.emplace_back(y1, y2, x1, x2);
    totx.emplace_back(x1, x2);
    toty.emplace_back(y1, y2);
    bot = max(bot, y1), top = min(top, y2);
    lef = max(lef, x1), rig = min(rig, x2);
  }
  if (bot <= top && lef <= rig) return 1;
  if (bot <= top) return check1(totx, k);
  if (lef <= rig) return check1(toty, k);
  return check2(rect, k);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("signal.inp", "r")) 
    freopen("signal.inp", "r", stdin),
    freopen("signal.out", "w", stdout);
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> a[i].x >> a[i].y >> a[i].s;
  ld lo = 0, hi = 1e15, mid, ans = -1;
  for (int i = 0; i < 80; ++i) {
    mid = (lo + hi) / 2.0;
    if (check(mid)) 
      ans = mid, hi = mid;
    else lo = mid;
  }
  cout << fixed << setprecision(9) << ans;
	return 0;
}


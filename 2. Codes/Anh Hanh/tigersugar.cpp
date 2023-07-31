#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int best;
ll solve(vector<pair<int, int>>& a) {
  vector<int> pos;
  for (auto& p : a) {
    int l, r; tie(l, r) = p;
    pos.emplace_back(l);
    pos.emplace_back(r);
  }
  sort(pos.begin(), pos.end());
  pos.erase(unique(pos.begin(), pos.end()), pos.end());
  int m = pos.size();
  vector<ll> bef(m + 1), aft(m + 1), cnt_b(m + 1), cnt_a(m + 1);
  for (auto p : a) {
    int l, r; tie(l, r) = p;
    int x = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
    int y = lower_bound(pos.begin(), pos.end(), r) - pos.begin();
    bef[y] += r, aft[x] += l, cnt_b[y]++, cnt_a[x]++;
  }
  for (int i = 1; i < m; ++i)
    bef[i] += bef[i-1], cnt_b[i] += cnt_b[i-1];
  for (int i = m-1; ~i; --i)
    aft[i] += aft[i+1], cnt_a[i] += cnt_a[i+1];
  
  
  ll res = 9e18, ans = -1;
  for (int i = 0; i < m; ++i) {
    ll cur = 0;
    if (i > 0) cur += pos[i] * cnt_b[i-1] - bef[i - 1];
    if (i < m-1) cur += aft[i + 1] - pos[i] * cnt_a[i + 1];
    
    if (cur < res) {
      res = cur, ans = pos[i];
    }
    
    res = min(res, cur);
    // kq moi diem p = (m*cnt_pre - pre) + (suf - m*cnt_suf)
    // = suf - pre + m*(cnt_pre - cnt_suf)
    // neu cnt_pre > cnt_suf -> m = l, kq = suf-pre + l*(cnt_pre-cnt_suf)
    // else m = r, kq = suf-pre +
  }
  best = ans;
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("tigersugar.inp", "r")) 
    freopen("tigersugar.inp", "r", stdin),
    freopen("tigersugar.out", "w", stdout);
  int n; cin >> n;
  vector<pair<int, int>> x, y;
  vector<tuple<int, int, int, int>> rect;
  for (int i = 0, x1, x2, y1, y2; i < n; ++i) {
    cin >> x1 >> y1 >> x2 >> y2;
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    x.emplace_back(x1, x2);
    y.emplace_back(y1, y2);
    rect.emplace_back(x1, y1, x2, y2);
  }
  vector<int> ans_x(n), ans_y(n);
  int bx = -1, by = -1;
  ll res = solve(x); bx = best;
  for (int i = 0, x1, x2, y1, y2; i < n; ++i) {
    tie(x1, y1, x2, y2) = rect[i];
    if (x2 < best) ans_x[i] = x2;
    else if (x1 > best) ans_x[i] = x1;
    else ans_x[i] = best;
  }
  res += solve(y); by = best;
  for (int i = 0, x1, x2, y1, y2; i < n; ++i) {
    tie(x1, y1, x2, y2) = rect[i];
    if (y2 < best) ans_y[i] = y2;
    else if (y1 > best) ans_y[i] = y1;
    else ans_y[i] = best;
  }
  cout << res << '\n';
  cout << bx << ' ' << by << '\n';
  for (int i = 0; i < n; ++i)
    cout << ans_x[i] << ' ' << ans_y[i] << '\n';
	return 0;
}
 
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
const int N = 1e5 + 5, INF = 1e9;
vector<tuple<int, int, int>> seg;
int n, m = 0, q;
ll c[N], bit1[N], bit2[N];
#define fi first
#define se second
void update(int i, int cv, ll v) {
  for (; i; i -= i & -i) 
    bit1[i] += cv, bit2[i] += v;
}
pair<ll, ll> get(int i) {
  ll res = 0, cnt = 0;
  if (i == 0) return {0, 0};
  for (; i <= m; i += i & -i) 
    cnt += bit1[i], res += bit2[i];
  return {res, cnt};
}
ll ans[N];

signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0, l, r; i < n; ++i)
    cin >> l >> r, c[m++] = l,
    seg.emplace_back(r, -1, l);
  sort(c, c + m); m = unique(c, c + m) - c;
  cin >> q;
  for (int i = 0, l, r; i < q; ++i) {
    cin >> l >> r;
    if (l > r) continue;
    seg.emplace_back(r, i, l);
  }
  sort(seg.begin(), seg.end());
  int pre = 0, max_l = -INF; // (pre, r]
  for (auto& p : seg) {
    int r, t, l; tie(r, t, l) = p;
    if (t == -1) {
      if (max_l != -INF) update(lower_bound(c, c + m, max_l) - c + 1, r - pre - 1, max_l * (r - pre - 1));
      max_l = max(max_l, l);
      update(lower_bound(c, c + m, max_l) - c + 1, 1, max_l);
      pre = r;
    } else {
      
      if (max_l != -INF) update(lower_bound(c, c + m, max_l) - c + 1, r - pre, max_l * (r - pre));
      pre = r;
      
      auto cur = get(lower_bound(c, c + m, l) - c + 1);
      ans[t] = cur.fi - (l - 1) * cur.se;
    }
  }
  for (int i = 0; i < q; ++i)
    cout << ans[i] << '\n';
	return 0;
}


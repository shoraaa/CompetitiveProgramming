#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define int ll

const int N = 1e5 + 5, LIM = 1e7 + 5;
const ll INF = 1e18;
ll s[N], p[N], x[N], c[N];
ll cnt[LIM], sum[LIM];
int n, m, q;

ll Cost(ll k) {
  // vi tri cuoi cung ma x[i] < k
  int lo = 0, hi = n - 1, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (x[mid] < k) ans = mid, lo = mid + 1;
    else hi = mid - 1;
  }
  return (ans == -1 ? 0 : c[ans]) + (k - x[ans]) * p[ans + 1];
}

ll Score(ll k) {
  // vi tri cuoi cung ma cnt[i] < k
  int lo = 0, hi = LIM, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (cnt[mid] < k) ans = mid, lo = mid + 1;
    else hi = mid - 1;
  }
  return (ans == -1 ? 0 : sum[ans]) + (k - cnt[ans]) * (ans + 1);
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("gapthu.inp", "r"))
    freopen("gapthu.inp", "r", stdin),
    freopen("gapthu.out", "w", stdout);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i)
    cin >> s[i];
  for (int i = 0; i <= n; ++i)
    cin >> p[i];
  
  ll total = 0;
  for (int i = 0, l, r; i < m; ++i)
    cin >> l >> r, cnt[l]++, cnt[r + 1]--, 
    total += r - l + 1;
    
  for (int i = 1; i < LIM; ++i) 
    cnt[i] += cnt[i - 1], 
    sum[i] = sum[i - 1] + i * cnt[i];
  for (int i = 1; i < LIM; ++i) cnt[i] += cnt[i - 1];

  ll cur = 0; ll tmp = total;
  for (int i = 0; i < n; ++i) {
    // cur + x[i]*p[i] >= s[i + 1]
    // x[i] >= ceil (s[i+1]-cur)/p[i]
    x[i] = min(tmp, (max(s[i + 1] - cur, 0LL) + p[i] - 1) / p[i]);
    c[i] = x[i] * p[i]; tmp -= x[i];
    cur += c[i];
    if (i) x[i] += x[i-1], c[i] += c[i-1];
  }
  x[n] = x[n - 1] + tmp; 
  c[n] = c[n - 1] + tmp * p[n];
  
  for (int i = 0; i < q; ++i) {
    ll t; cin >> t;
    ll lo = 1, hi = total, mid, ans = -1;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (Score(mid) - Cost(mid) >= t) ans = mid, hi = mid - 1;
      else lo = mid + 1;
    }
    cout << ans << ' ';
  }
    
	return 0;
}


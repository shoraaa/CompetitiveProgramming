#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
const ll INF = 1e18;

int a[N], neg[N];
ll f[N];
int n;

ll c[N];
int m;

pair<ll, int> bit[N], dp[N];

#define fi first
#define se second

pair<ll, int> get(ll i) {
  i = upper_bound(c, c + m, i) - c;
  pair<ll, int> res = make_pair(-INF, 0);
  for (; i; i -= i & -i) {
    res = max(res, bit[i]);
  }
  return res;
}

void update(ll i, ll x, int y) {
  pair<ll, int> v = make_pair(x, y);
  i = lower_bound(c, c + m, i) - c + 1;
  for (; i <= m; i += i & -i) {
    bit[i] = max(bit[i], v);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> n; m = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      f[i] = f[i - 1] + a[i];
      
      c[m++] = f[i] + a[i];
      neg[i] = 0;
    }
    
    sort(c, c + m);
    m = unique(c, c + m) - c;
    for (int i = 1; i <= m; ++i) {
      bit[i].fi = bit[i].se = 0;
    }
    
    a[0] = a[n + 1] = 1e9 + 9;
    
    for (int i = 1; i <= n; ++i) {
      dp[i] = make_pair(-INF, 0);
      
      if (-a[i] + min(a[i - 1], a[i + 1]) <= 0) {
        continue;
      }
      
      dp[i] = make_pair(ll(a[i]), 0);

      
      pair<ll, int> val = get(f[i - 1] - a[i] - 1);
      val.fi += a[i];
      dp[i] = max(dp[i], val);
      update(f[i] + a[i], dp[i].fi, i);
      
      // for (int j = i - 1; j; --j) {
        // if (f[j] + a[j] < f[i - 1] - a[i]) {
          // dp[i] = max(dp[i], make_pair(dp[j].fi + a[i], j));
        // }
      //}
      
      // cerr << dp[i].fi << '\n';
    }
    
    // lay vi tri i ma f[n] - f[i] - a[i] > 0
    pair<ll, int> res = make_pair(-INF, 0);
    
    for (int i = 1; i <= n; ++i) {
      res = max(res, make_pair(dp[i].fi, -i));
    }
    
    // cout << f[n] - res.fi * 2 << '\n';
    
    int i = -res.se;
    while (i > 0) {
      neg[i] = 1;
      i = dp[i].se;
    }
    for (int i = 1; i <= n; ++i) {
      if (neg[i]) cout << -a[i] << ' ';
      else cout << a[i] << ' ';
    }
    cout << '\n';
    
    
  }
	return 0;
}


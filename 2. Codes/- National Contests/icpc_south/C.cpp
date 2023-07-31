#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 1e18;
const int N = 5005;
ll a[N], x[N], w[N], xw[N], dp[N][N][2];
pair<int, int> b[N];
int n, k;
#define int ll
#define fi first
#define se second

inline ll mul(ll x, ll y) {
  return x * y;
}

struct ConvexHull {
  deque<pair<ll, ll>> dq;
  ll value(pair<ll, ll> l, ll x) {
    return mul(l.fi, x) + l.se;
  }
  bool better(pair<ll, ll> L, pair<ll, ll> L1, pair<ll, ll> L2) {
    return mul(L2.se - L.se, L1.fi - L2.fi) >= mul(L.fi - L2.fi, L2.se - L1.se);
  }
  void add(ll m, ll b) {
    while((int)dq.size() >= 2 && better({m, b}, dq[dq.size() - 1], dq[dq.size() - 2])) dq.pop_back();
    dq.push_back({m, b});
  }
  ll get(ll x) {
    while((int)dq.size() >= 2 && value(dq[0], x) > value(dq[1], x)) dq.pop_front();
    return value(dq.front(), x);
  }
} cht[2];

ll get(ll x, int t) {
  return cht[t].get(x);
}
void upd(ll A, ll B, int t) {
  cht[t].add(A, B);
}
void clear() {
  for (int t = 0; t <= 1; ++t) cht[t].dq.clear();
}
signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; ++i)
    cin >> b[i].fi >> b[i].se;
  sort(b + 1, b + n + 1);
  for (int i = 1; i <= n; ++i) 
    x[i] = b[i].fi, w[i] = b[i].se, a[i] = x[i],
    xw[i] = xw[i-1] + x[i] * w[i],
    x[i] += x[i-1], w[i] += w[i-1];
  for (int i = 0; i <= k; ++i) for (int j = 0; j <= n; ++j) dp[i][j][0] = dp[i][j][1] = 2.5e15 + 123;
  dp[0][0][1] = 0;
  for (int d = 1; d <= k; ++d) {
    upd(0, 0, 0); upd(0, 0, 1); 
    for (int i = 1; i <= n; ++i) {
      // tim j<i va lay j+1->i-1 vao i
      // dp[d][i] = a[i] * w[i] - xw[i] + (a[i] * -w[j] + xw[j] + dp[d-1][j][1])
      dp[d][i][0] = a[i] * w[i] - xw[i] + get(-a[i], 0);
      // tim j<i va lay j+1->i vao j
      // dp[d][i] = xw[i] -a[j] * w[i] + (a[j] * w[j] - xw[j] + dp[d][j][0])
      dp[d][i][1] = min(dp[d][i][0], xw[i] + get(-w[i], 1));

      upd(w[i], xw[i] + dp[d-1][i][1], 0);
      upd(a[i], a[i]*w[i] - xw[i] + dp[d][i][0], 1);
    }
    clear();
    
  }
  cout << dp[k][n][1];
	return 0;
}


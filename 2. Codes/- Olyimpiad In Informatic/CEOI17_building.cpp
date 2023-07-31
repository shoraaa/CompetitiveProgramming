#include<bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int N = 1e5 + 5;
const ll INF = 1e12;
const ll LLINF = 1e18;
ll h[N], w[N];
int n;
 
ll dp[N];
 
ll sqr(ll x) {
  return x * x;
}
 
namespace task1 {
  void solve() {
    dp[1] = 0;
    for (int i = 2; i <= n; ++i) {
      dp[i] = LLINF;
      for (int j = i - 1; j; --j) {
        dp[i] = min(dp[i], dp[j] + sqr(h[i] - h[j]) + (w[i - 1] - w[j]));
      }
    }
    cout << dp[n];
  }
}
 
namespace task2 {
  const int C = 1e6;
  
  struct Line {
    ll a, b;
    Line(ll a = INF, ll b = INF): a(a), b(b) {}
    ll get(ll x) {
      return a * x + b;
    }
  };
  
  struct LichaoTree {
    Line v; ll x, res;
    Line lct[(C + 1) * 4];
    void update(int i, int l, int r) {
      int m = (l + r) / 2;
      if (v.a < lct[i].a) swap(v, lct[i]);
      if (v.get(m) < lct[i].get(m)) {
        swap(v, lct[i]);
        if (l != r) update(i * 2 + 1, m + 1, r);
      } else {
        if (l != r) update(i * 2, l, m);
      }
    }
    
    void get(int i, int l, int r) {
      res = min(res, lct[i].get(x));
      if (l == r) return;
      int m = (l + r) / 2;
      if (x <= m) get(i * 2, l, m);
      else get(i * 2 + 1, m + 1, r);
    }
    
    void update(ll a, ll b) {
      v = Line(a, b);
      update(1, 0, C);
    }
    
    ll get(ll x) {
      res = LLINF;
      this->x = x;
      get(1, 0, C);
      return res;
    }
    
  } lct;
  
  void solve() {
    dp[1] = 0;
    lct.update(-2 * h[1], dp[1] + sqr(h[1]) - w[1]);
    for (int i = 2; i <= n; ++i) {
      // dp[i] = h[i]^2 + w[i-1] + MIN[(-2h[j]) * h[i] + dp[j] + h[j]^2 - w[j]]
      dp[i] = sqr(h[i]) + w[i-1] + lct.get(h[i]);
      lct.update(-2 * h[i], dp[i] + sqr(h[i]) - w[i]);
    }
    cout << dp[n];
  }
}
 
 
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> h[i];
  for (int i = 1; i <= n; ++i)
    cin >> w[i],
    w[i] += w[i - 1];
    
  if (n <= 1000) task1::solve();
  else task2::solve();
  
	return 0;
}
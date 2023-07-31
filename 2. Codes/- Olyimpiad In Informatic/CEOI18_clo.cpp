#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 4005 * 50;

struct Item {
  int f, t, c, v;
  bool operator < (const Item& b) const {
    if (f == b.f) return t < b.t;
    return f > b.f;
  }
} a[N];

int n, m;

const ll INF = 1e15;
ll dp[2][N];
void cmax(ll& x, ll y) { x = max(x, y); }

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; 
  int W = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].c >> a[i].f >> a[i].v;
    a[i].t = 0;
    W += a[i].c;
  }
  cin >> m;
  for (int i = n + 1; i <= n + m; ++i) {
    cin >> a[i].c >> a[i].f >> a[i].v;
    a[i].t = 1;
  }
  n += m;
  sort(a + 1, a + n + 1);
  
  for (int j = 0; j <= W; ++j) {
    dp[0][j] = -INF;
  }
  dp[0][0] = 0;
  
  for (int i = 0; i < n; ++i) {
    int cu = i & 1, nx = cu ^ 1;
    
    for (int j = 0; j <= W; ++j) {
      dp[nx][j] = -INF;
    }
    
    for (int j = 0; j <= W; ++j) {
      if (dp[cu][j] == -INF) continue;
      
      // ko chon thang i + 1
      cmax(dp[nx][j], dp[cu][j]);
      
      // chon thang i + 1
      if (a[i + 1].t == 0) {
        cmax(dp[nx][j + a[i + 1].c], dp[cu][j] - a[i + 1].v);
      } else {
        
        if (j >= a[i + 1].c) {
          cmax(dp[nx][j - a[i + 1].c], dp[cu][j] + a[i + 1].v);
        }
        
      }
      
    }
  }
  
  ll res = 0;
  for (int i = 0; i <= W; ++i) {
    cmax(res, dp[n & 1][i]);
  }
  cout << res;
  
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
const int INF = 1e9;

int lef[N][41], dp[N];

int solve(const vector<int>& a) {
  int n = a.size(), m = 40;
  
  // for (ll x : a) {
    // cerr << x << ' ';
  // }
  // cerr << endl;
  
  // lef[i][d] = j ma tu j->i tao dc thanh d
  // lef[i][d] = lef[lef[i][d - 1] - 1][d - 1]
  
  for (int i = 1; i <= n; ++i) {
    for (int d = 0; d <= m; ++d) {
      lef[i][d] = 0;
    }
    lef[i][a[i - 1]] = i;
  }
  
  for (int d = 1; d <= m; ++d) {
    
    for (int i = 1; i <= n; ++i) {
      int j = lef[i][d - 1];
      if (j > 1) {
        lef[i][d] = lef[j - 1][d - 1];
      }
    }
    
  }
  
  for (int i = 1; i <= n; ++i) {
    dp[i] = INF;
    for (int d = 0; d <= m; ++d) {
      int j = lef[i][d];
      if (j) {
        dp[i] = min(dp[i], dp[j - 1] + 1);
      }
    }
  }
  
  return dp[n];
  
}

ll a[N], b[N];
int n, m;

#define get_x(x) (__builtin_ctzll(x))
#define get_y(y) (y >> get_x(y))

int solve() {
  int res = 0;
  
  for (int i = 1; i <= n;) {
    if (a[i] == 0) {
      
      res += 1;
      while (i <= n && a[i] == 0) i++;
      
    } else {
      vector<int> vec;

      ll y = get_y(abs(a[i]));
      
      while (i <= n && a[i] != 0) {
        
        if (get_y(abs(a[i])) != y) break;
        
        vec.emplace_back(get_x(abs(a[i])));
        i++;
      }
      
      res += solve(vec);
      
      
    }
    
  }
  
  return res;
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1, x; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> x;
      a[i] += x;
      b[j] += x;
    }
  }
  
  ll res = solve();
  swap(a, b);
  swap(n, m);
  res *= solve();
  cout << res;
	return 0;
}


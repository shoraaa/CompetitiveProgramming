#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005, M = 1e9 + 7;
int n, b;
int a[N], dp[N][N], f[N][N];

void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("graph.inp", "r")) {
    freopen("graph.inp", "r", stdin);
    freopen("graph.out", "w", stdout);
  }
  
  cin >> n >> b;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  dp[0][0] = 1;
  for (int i = 0; i <= n; ++i) {
    
    for (int j = 1; j <= b; ++j) {
      add(f[i][j], f[i][j - 1]);
    }
    
    for (int j = 0; j <= b; ++j) {
      add(dp[i][j], f[i][j]);
    }
    
    if (i == n) continue;
    
    if (a[i + 1] == -1) {
      
      // cho thang fi = 0
      for (int j = 0; j <= b; ++j) {
        add(dp[i + 1][j], dp[i][j]);
      }
      
      // cho thang fi > 0 <> fi <= min(i-1, b)
      int lim = min(i, b);
      for (int j = 0; j <= b; ++j) {
        add(dp[i + 1][j + 1], 1LL * dp[i][j] * min(lim, j + 1) % M);
        
        if (j + 2 <= lim) {
          
          add(f[i + 1][j + 2], dp[i][j]);
          add(f[i + 1][lim + 1], M - dp[i][j]);
      
          // for (int k = j + 2; k <= lim; ++k) {
            // add(dp[i + 1][k], dp[i][j]);
          // }
          
        }
        
      }
      
      
    } else {
      
      if (a[i + 1] == 0) {
        
        // fi = 0
        for (int j = 0; j <= b; ++j) {
          add(dp[i + 1][j], dp[i][j]);
        }
        
      } else {
        
        if (a[i + 1] > b) {
          cout << 0;
          return 0;
        }
        
        // fi
        for (int j = 0; j <= b; ++j) {
          add(dp[i + 1][max(j + 1, a[i + 1])], dp[i][j]);
        }
        
      }
      
    }
  }
  
  int res = 0;
  for (int i = 0; i <= b; ++i) {
    add(res, dp[n][i]);
  }
  cout << res;
  
	return 0;
}


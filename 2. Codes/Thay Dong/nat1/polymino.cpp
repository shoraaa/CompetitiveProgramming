#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 305, M = 1e9 + 7;

void add(int& x, int y) {
  x += y; 
  if (x >= M) x -= M;
  if (x < 0) x += M;
}

int dp[N][N][N], f[N][N][N], g[N][N][N];
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  // f[i][l][r] la so hinh xet grid i truc, hang tren cung di xuong o truc l va r
  // f[i][l][r] -> f[i + 1][l][m + 1], f[i][l][r] -> f[i + 1][m + 1][r + 1]
  // chen them mot cot vao giua cot m va m+1
  // -> cot moi co chi so la m+1 va day chi so cua r sang phai thanh r+1
  int res = 0;
  dp[2][1][2] = 1;
  for (int i = 2; i <= n; ++i) {
    
    for (int l = 1; l <= i; ++l) 
      for (int r = l + 1; r <= i; ++r)
        add(f[i][l][r], f[i][l][r - 1]);
    
    for (int r = 1; r <= i; ++r)
      for (int l = 1; l <= r - 1; ++l)
        add(g[i][r][l], g[i][r][l - 1]);
    
    for (int l = 1; l <= i; ++l) for (int r = l + 1; r <= i; ++r) {
      add(dp[i][l][r], f[i][l][r]);
      add(dp[i][l][r], g[i][r][l]);
      
      if (!dp[i][l][r]) continue;
      
      if (i == n) {
        add(res, dp[i][l][r]); continue;
      }
      
      if (r == i) add(dp[i + 1][l][r + 1], dp[i][l][r]);
      if (l == 1) add(dp[i + 1][l][r + 1], dp[i][l][r]);
      
      // cap nhat doan dp[i + 1][l][m] voi moi m = [l + 1, r]
      add(f[i + 1][l][l + 1], dp[i][l][r]), add(f[i + 1][l][r + 1], -dp[i][l][r]);
      
      // cap nhat doan dp[i + 1][m][r + 1] voi moi m = [l + 1, r]
      add(g[i + 1][r + 1][l + 1], dp[i][l][r]), add(g[i + 1][r + 1][r + 1], -dp[i][l][r]);
      
      
      // for (int m = l; m <= r - 1; ++m) {
        // dp[i + 1][l][m + 1] += dp[i][l][r];
        // dp[i + 1][m + 1][r + 1] += dp[i][l][r];
      // }
    }
    
  }
  cout << res;
  
	return 0;
}


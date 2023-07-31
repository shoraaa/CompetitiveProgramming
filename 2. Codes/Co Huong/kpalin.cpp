#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 155;
int dp[3][N][N][102], pw[N];
int n, m, M;

inline void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
inline void sub(int& x, int y) {
  x -= y; if (x < 0) x += M;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("kpalin.inp", "r")) 
    freopen("kpalin.inp", "r", stdin),
    freopen("kpalin.out", "w", stdout);
  cin >> n >> m >> M;
  // dp[len][l][r][mod] la so xau con trong doan l r co do dai = len va chia m du mod
  string s; cin >> s; s = '@' + s + '$';
  
  pw[0] = 1;
  for (int i = 1; i < N; ++i) 
    pw[i] = pw[i-1] * 10 % m; 
  
  for (int l = 1; l <= n; ++l) for (int r = l-1; r <= n; ++r) dp[0][l][r][0] = 1;
  for (int i = 1; i <= n; ++i) dp[1][i][i][(s[i] - '0') % m] = 1;
  for (int len = 2; len <= n; ++len) for (int l = 1; l + len - 1 <= n; ++l) {
    int r = l + len - 1;
    for (int mod = 0; mod < m; ++mod) {
      add(dp[1][l][r][mod], dp[1][l+1][r][mod]);
      add(dp[1][l][r][mod], dp[1][l][r-1][mod]);
      sub(dp[1][l][r][mod], dp[1][l+1][r-1][mod]);
    }
  }
  int res = dp[1][1][n][0]; 
  for (int i = 2; i <= n; ++i) {
    int cur = i % 3, pre2 = (i - 2 + 3) % 3;
    memset(dp[cur], 0, sizeof(dp[cur]));
    for (int len = i; len <= n; ++len) for (int l = 1; l + len - 1 <= n; ++l) {
      int r = l + len - 1;
      if (s[l] == s[r]) {
        
        int x = s[l] - '0';
        if (i == 2) {
          int mod2 = (x * 10 + x) % m;
          add(dp[cur][l][r][mod2], 1);
          continue;
        }
        
        for (int mod_ = 0; mod_ < m; ++mod_) {
          // (x * 10^(len-1) + mod_) * 10 + x = mod
          // mod_ = (mod - x) * inv[10] * inv[x] - 10^(len-1)
          // xau rong -> x * 10 + x
          int mod2 = (x * pw[i-2] + mod_) * 10 + x; mod2 %= m;
          add(dp[cur][l][r][mod2], dp[pre2][l+1][r-1][mod_]);
        }
      }
    }
    for (int len = i; len <= n; ++len) for (int l = 1; l + len - 1 <= n; ++l) {
      int r = l + len - 1;
      for (int mod = 0; mod < m; ++mod) {
        add(dp[cur][l][r][mod], dp[cur][l+1][r][mod]);
        add(dp[cur][l][r][mod], dp[cur][l][r-1][mod]);
        sub(dp[cur][l][r][mod], dp[cur][l+1][r-1][mod]);
      }
    }
    add(res, dp[cur][1][n][0]);
  }
  cout << res;
  
	return 0;
}


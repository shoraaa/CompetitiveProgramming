#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 50 + 5;
string s[2], tt[N];
int f[2][26][N][N], dp[N][N], from[N], to[N][2];
int m, n[2];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  for (int t = 0; t < 2; ++t)
    cin >> s[t], n[t] = s[t].size(), s[t] = ' ' + s[t];
  cin >> m;
  for (int i = 0; i < m; ++i)
    cin >> tt[i], 
    from[i] = tt[i][0] - 'a',
    to[i][0] = tt[i][3] - 'a',
    to[i][1] = tt[i][4] - 'a';
  for (int t = 0; t < 2; ++t) {
    for (int l = 1; l < n[t]; ++l) for (int i = 0; i < m; ++i)
      if (s[t][l] == tt[i][3] && s[t][l+1] == tt[i][4])
        f[t][from[i]][l][l+1] = 1;
    for (int l = 1; l <= n[t]; ++l)
      f[t][s[t][l] - 'a'][l][l] = 1;
    for (int len = 3; len <= n[t]; ++len) for (int l = 1; l + len - 1 <= n[t]; ++l) {
      int r = l + len - 1; 
      for (int k = l; k <= r; ++k) for (int i = 0; i < m; ++i) 
        f[t][from[i]][l][r] |= f[t][to[i][0]][l][k] && f[t][to[i][1]][k+1][r];
    }
  }
  memset(dp, 0x3f, sizeof(dp)); int inf = dp[0][0];
  dp[0][0] = 0;
  for (int i = 0; i < n[0]; ++i) for (int j = 0; j < n[1]; ++j) if (dp[i][j] != inf) {
    if (s[0][i+1] == s[1][i+1]) dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + 1);
    for (int u = i+1; u <= n[0]; ++u) for (int v = j+1; v <= n[1]; ++v) 
      for (int c = 0; c < 26; ++c) if (f[0][c][i+1][u] && f[1][c][j+1][v])
        dp[u][v] = min(dp[u][v], dp[i][j] + 1); 
    
  }
  cout << (dp[n[0]][n[1]] == inf ? -1 : dp[n[0]][n[1]]);
	return 0;
}


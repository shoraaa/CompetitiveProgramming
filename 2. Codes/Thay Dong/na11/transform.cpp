#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 305, M = 1005;
string s; 
int c[M], p[M], q[M], dp[N][N], g[40][40], mask[4][4][1 << 7][1 << 7];
int n, m;

#define bit(x, i) ((x) & (1 << (i)))
#define shift(x, i) ((x) >> ((i) * 7)) & ((1 << 7) - 1)

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> s >> m; string t; char ch;
  for (int i = 0; i < m; ++i) {
    cin >> ch >> t; 
    c[i] = ch - 'a', p[i] = t[0] - 'a', q[i] = t[1] - 'a';
    g[p[i]][q[i]] |= 1 << c[i];
      
  }
  
  for (int c1 = 0; c1 < 4; ++c1) for (int c2 = 0; c2 < 4; ++c2)
    for (int msk1 = 0; msk1 < 1 << 7; ++msk1) for (int msk2 = 0; msk2 < 1 << 7; ++msk2)
      for (int i = 0; i < 7; ++i) if (msk1 >> i & 1) for (int j = 0; j < 7; ++j) if (msk2 >> j & 1)
        mask[c1][c2][msk1][msk2] |= g[c1 * 7 + i][c2 * 7 + j];
  
  
  n = s.size(); s = ' ' + s;
  for (int i = 1; i <= n; ++i) dp[i][i] |= 1 << (s[i] - 'a');
  for (int i = 1; i <= n - 1; ++i) for (int j = 0; j < m; ++j) 
    if (s[i] == p[j] + 'a' && s[i + 1] == q[j] + 'a')
      dp[i][i + 1] |= 1 << c[j];
  
  for (int len = 3; len <= n; ++len) for (int l = 1; l + len - 1 <= n; ++l) {
    int r = l + len - 1;
    for (int k = l; k <= r; ++k) {
      
      for (int c1 = 0; c1 < 4; ++c1) for (int c2 = 0; c2 < 4; ++c2)
        dp[l][r] |= mask[c1][c2][shift(dp[l][k], c1)][shift(dp[k+1][r], c2)];
      
    }
  }
  string res;
  for (int c = 0; c < 26; ++c) 
    if (bit(dp[1][n], c)) res += c + 'a';
  if (res.empty()) 
    res = "No Solution.";
  cout << res;
	return 0;
}

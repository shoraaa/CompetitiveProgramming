#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 405;
string s;
vector<int> pos[3];
int n;

inline void cmin(int& x, int y) { x = min(x, y); }

int dp[N][N][N][3], f[3][3][N][N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> s; for (int i = 0; i < 3; ++i) pos[i].emplace_back(-1);
  for (int i = 0; i < n; ++i)
    if (s[i] == 'R') pos[0].emplace_back(i);
    else if (s[i] == 'G') pos[1].emplace_back(i);
    else pos[2].emplace_back(i);
    
  for (int u = 0; u < 3; ++u) for (int v = 0; v < 3; ++v) if (u != v) {
    for (int i = 0; i < pos[u].size(); ++i) for (int j = 0; j < pos[v].size(); ++j) 
      f[u][v][i][j] = (j ? f[u][v][i][j - 1] : 0) + (pos[u][i] < pos[v][j]);  
  }  
  
  memset(dp, 0x3f, sizeof(dp)); dp[0][0][0][0] = 0; int inf = dp[0][0][0][1];
  for (int i = 0; i < pos[0].size(); ++i) for (int j = 0; j < pos[1].size(); ++j) for (int k = 0; k < pos[2].size(); ++k) {
    int p = i + j + k;
    if (p == 0) cmin(dp[i+1][j][k][0], max(0, pos[0][i+1]-p));
    cmin(dp[i][j+1][k][1], dp[i][j][k][0] + max(0, pos[1][j+1]+f[1][0][j+1][i]+f[1][2][j+1][k]-p));
    cmin(dp[i][j][k+1][2], dp[i][j][k][0] + max(0, pos[2][k+1]+f[2][0][k+1][i]+f[2][1][k+1][j]-p));
    
    cmin(dp[i+1][j][k][0], dp[i][j][k][1] + max(0, pos[0][i+1]+f[0][1][i+1][j]+f[0][2][i+1][k]-p));
    cmin(dp[i][j][k+1][2], dp[i][j][k][1] + max(0, pos[2][k+1]+f[2][0][k+1][i]+f[2][1][k+1][j]-p));
    
    cmin(dp[i+1][j][k][0], dp[i][j][k][2] + max(0, pos[0][i+1]+f[0][1][i+1][j]+f[0][2][i+1][k]-p));
    cmin(dp[i][j+1][k][1], dp[i][j][k][2] + max(0, pos[1][j+1]+f[1][0][j+1][i]+f[1][2][j+1][k]-p));
  }  
  
  int res = 1e9;
  for (int i = 0; i < 3; ++i)
    cmin(res, dp[pos[0].size() - 1][pos[1].size() - 1][pos[2].size() - 1][i]);
  cout << (res == 1e9 ? -1 : res);
	return 0;
}


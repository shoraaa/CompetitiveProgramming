#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 250 + 5;
int n, m; string s, t[N];
bitset<N> del[N], dp[N][35][25];
int cost[N][N];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> s, n = s.size(), s = ' ' + s;
  cin >> m;
  for (int i = 0; i < m; ++i)
    cin >> t[i];
  
  for (int i = 1; i <= n; ++i) for (int k = 0; k < m; ++k)
    dp[i][k][0][i-1] = 1;
  for (int i = n; i; --i) for (int k = 0; k < m; ++k) {
    for (int j = i-1; j < n; ++j) {
      for (int l = 0; l <= t[k].size(); ++l) if (dp[i][k][l][j]) {
        dp[i][k][l] |= del[j + 1];
        if (s[j + 1] == t[k][l])
          dp[i][k][l + 1][j + 1] = 1;
      }
      del[i] |= dp[i][k][t[k].size()];
    }
  }
  memset(cost, 0x3f, sizeof(cost));
  for (int i = 1; i <= n + 1; ++i) cost[i][i-1] = 0;
  for (int l = 1; l <= n; ++l) for (int i = 1; i + l - 1 <= n; ++i) {
    int j = i + l - 1;
    if (del[i][j]) cost[i][j] = 0;
    else {
      for (int v = i; v <= j; ++v)
        cost[i][j] = min(cost[i][j], cost[i][v-1] + cost[v+1][j] + 1);
    }
  }
  cout << cost[1][n];
	return 0;
}


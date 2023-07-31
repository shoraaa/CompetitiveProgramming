#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5000 + 5, M = 1e9 + 7;
int dp[N][N], p[N], nxt[N][26];
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
int n, m;
string s;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> m >> s; n = s.size();
  s = ' '  + s; m -= n;
  if (m == 0)
    return cout << 1, 0;
  for (int i = 2; i <= n; ++i) {
    int k = p[i-1];
    while (k > 0 && s[k + 1] != s[i]) k = p[k];
    if (s[k + 1] == s[i]) 
      p[i] = k + 1;
  }
  for (int i = 0; i <= n; ++i) for (int c = 0; c < 26; ++c) {
    if (s[i + 1] == c + 'a')
      nxt[i][c] = i + 1;
    else
      nxt[i][c] = nxt[p[i]][c]; 
  }
  dp[1][1] = 1; // s[0]
  for (int i = 1; i <= m-1; ++i) for (int j = 1; j <= n; ++j) {
    for (int c = 0; c < 26; ++c) 
      add(dp[i + 1][nxt[j][c]], dp[i][j]);
  }
  int res = 0;
  for (int i = 1; i <= n; ++i)
    add(res, dp[m][i]);
  cout << res;
	return 0;
}


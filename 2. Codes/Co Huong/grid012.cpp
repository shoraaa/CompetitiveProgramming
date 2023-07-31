#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1005;
string s[N];
int n, m;

bitset<4*N> dp[N][N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("grid012.in", "r"))
    freopen("grid012.in", "r", stdin),
    freopen("grid012.out", "w", stdout);
  
  int T; cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
      cin >> s[i];
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
      dp[i][j].reset();
    dp[0][1][0] = 1;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
      int x = s[i][j - 1] - '0';
      dp[i][j] = (dp[i-1][j] << x) | (dp[i][j-1] << x);
    }
    
    for (int x = 0; x <= n*4; ++x) if (dp[n][m][x])
      cout << x << ' ';
  }
	return 0;
}


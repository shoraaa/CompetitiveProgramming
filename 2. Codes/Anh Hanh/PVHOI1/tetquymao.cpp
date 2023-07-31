#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 65, M = 1e9 + 19772207;
vector<int> nxt[1 << 6][1 << 6];
int n, m;
int a[N], dp[N][1 << 6][1 << 6];

#define bit(_, _i) (_ & (1 << _i))
#define bitcount(_) (__builtin_popcount(_))

int solve(int cd_i, int cd_j) {
  memset(dp, 0, sizeof(dp));
  for (int x = 0; x < 1 << m; ++x) {
    if (a[0] != 3 && bitcount(x) % 3 != a[0]) continue;
    if (0 == cd_i && !bit(x, cd_j)) continue;
    dp[0][0][x] = 1;
  }
  for (int i = 1; i < n; ++i) {
    for (int x = 0; x < 1 << m; ++x) {
      for (int y = 0; y < 1 << m; ++y) {
        if (!dp[i - 1][x][y]) continue;
        
        for (int z : nxt[x][y]) {
          if (a[i] != 3 && bitcount(z) % 3 != a[i]) continue;
          if (i == cd_i && !bit(z, cd_j)) continue;
          dp[i][y][z] += dp[i - 1][x][y];
          if (dp[i][y][z] >= M) dp[i][y][z] -= M;
        }
        
      }
    }
  }
  int res = 0;
  for (int x = 0; x < 1 << m; ++x) {
    for (int y = 0; y < 1 << m; ++y) { 
      if (!dp[n - 1][x][y]) continue;
      res += dp[n - 1][x][y];
      if (res >= M) res -= M;
    }
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("tetquymao.inp", "r"))
    freopen("tetquymao.inp", "r", stdin),
    freopen("tetquymao.out", "w", stdout);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) 
    cin >> a[i];
    
  for (int x = 0; x < 1 << m; ++x) {
    for (int y = 0; y < 1 << m; ++y) {
      for (int z = 0; z < 1 << m; ++z) {
        int flag = 1;
        for (int i = 0; i < m; ++i) if (bit(z, i)) {
          if (i >= 1 && bit(x, i - 1)) flag = 0;
          if (i < m - 1 && bit(x, i + 1)) flag = 0;
          if (i >= 2 && bit(y, i - 2)) flag = 0;
          if (i < m - 2 && bit(y, i + 2)) flag = 0;
          if (!flag) break;
        }
        if (flag) nxt[x][y].emplace_back(z);
      }
    }
  }
  
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << solve(i, j) << ' ';
    }
    cout << '\n';
  }
  
	return 0;
}


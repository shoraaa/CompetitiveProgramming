#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int INF = 1e9;

int n, m, k;
vector<vector<int>> a, f, dow, rig;

int solve(int c) {
  int res = 0;
  
  f = vector<vector<int>>(n + 5, vector<int>(m + 5));
  
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      
      f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
      int x = (a[i][j] + f[i][j]) % 3;
      
      if (x == c) continue;
      
      x = c - x;
      if (x < 0) x += 3;
      
      
      if (!dow[i][j]) {
        return INF;
      }
      
      f[i][j] += x;
      f[dow[i][j] + 1][j] -= x;
      f[i][rig[i][j] + 1] -= x;
      f[dow[i][j] + 1][rig[i][j] + 1] += x;
      
      res += x;
    
      
    }
  }
  
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> k;
  a.resize(n + 5, vector<int>(m + 5));
  f = dow = rig = a;
  
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
    }
  }
  
  for (int i = 1, r, c, x, y; i <= k; ++i) {
    cin >> r >> c >> x >> y;
    dow[r][c] = x;
    rig[r][c] = y;
  }
  
  int res = min(solve(1), solve(2));
  if (res == INF) {
    cout << -1;
    return 0;
  }
  cout << res;
  
	return 0;
}


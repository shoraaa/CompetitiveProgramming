#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1505;
int a[N][N], dp[N][N]; ll bit[N][N];
int n;

ll get(int i, int j) {
  if (i == 0 && j == 1) return 0;
  if (i == 0 || j == 0) return -1e9; 
  ll res = 0;
  for (; j; j -= j & -j) res += bit[i][j];
  return res;
}

void update(int i, int j, int v) {
  for (; j <= n; j += j & -j) bit[i][j] += v;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; 
  for (int i = 0; i <= n; ++i) dp[i][0] = dp[0][i] = -1e9;
  dp[0][1] = 0;
  ll sum = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      cin >> a[i][j], dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + a[i][j],
      update(i, j, dp[i][j]), update(i, j + 1, -dp[i][j]), sum += dp[i][j];
  cout << sum << '\n';
  for (int t = 0, x, y; t < n; ++t) {
    char c; cin >> c >> x >> y; 
    int v = c == 'U' ? 1 : -1;
    a[x][y] += v; int res = 0;
    for (int i = x, l = y, r = y-1; i <= n; ++i) {
      while (l <= n && max(get(i, l-1), get(i-1, l)) + a[i][l] == get(i, l)) l++;
      res += v * (r - l + 1); update(i, l, v); update(i, r + 1, -v);
      while (r+1 <= n && max(get(i, r), get(i-1, r+1)) + a[i][r+1] != get(i, r+1)) 
        dp[i][r+1] = max(get(i, r), get(i-1, r+1)) + a[i][r+1], 
        update(i, r+1, v), update(i, r+2, -v), res += v, r++;
      if (l > r) break;
    }
    sum += res;
    cout << sum << '\n';
  }
	return 0;
}


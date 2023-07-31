#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 3000;
int n, m;
string str;
char mp[MAXN+2][MAXN+2];
int ans;
 
int check(int x, int y) {
  return 1 * (mp[x-1][y] == 'R') * (mp[x][y] == 'G') * (mp[x+1][y] == 'W')
       + 2 * (mp[x][y-1] == 'R') * (mp[x][y] == 'G') * (mp[x][y+1] == 'W');
}
 
signed main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> str;
    for (int j = 1; j <= m; j++)
      mp[i][j] = str[j-1];
  }
  for (int i = 1; i <= n+m-1; i++) {
    int x = min(i, n), y = max(1, i-n+1);
    int V = 0, H = 0, No = 0;
    while (x >= 1 && y <= m) {
      int t = check(x, y);
      int tmp = max(V, H);
      if (t & 1) V = max(V, No) + 1;
      if (t & 2) H = max(H, No) + 1;
      No = tmp;
      x--, y++;
    }
    ans += max({V, H, No});
  }
  cout << ans << "\n";
}

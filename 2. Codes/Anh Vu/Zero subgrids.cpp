#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 5;
int a[N][2], nxt[N][3];
ll f[N][3];
map<ll, int> pos[3];
pair<int, int> dp[N][2]; // {val lon nhat, j nho nhat <= i tm dp[i][j] = val}
#define fi first
#define se second
int n;

void cmax(pair<int, int>& x, pair<int, int> y) {
  y.fi += 1;
  if (y.fi > x.fi) x = y;
  else if (y.fi == x.fi && y.se < x.se) x = y;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int h = 0; h < 2; ++h) for (int i = 1; i <= n; ++i)
    cin >> a[i][h], f[i][h] = f[i-1][h] + a[i][h];
  for (int i = 1; i <= n; ++i)
    f[i][2] = f[i-1][2] + a[i][0] + a[i][1];
  for (int i = n; i; --i) {
    // vi tri j nao do ma f[j] == f[i-1]
    for (int h = 0; h < 3; ++h) {
      pos[h][f[i][h]] = i;
      nxt[i][h] = pos[h][f[i - 1][h]] ? pos[h][f[i - 1][h]] : nxt[i + 1][h];
      if (nxt[i + 1][h] && nxt[i + 1][h] < nxt[i][h]) nxt[i][h] = nxt[i + 1][h];
    }
  }
  
  for (int i = 0; i <= n; ++i) {
    // hang tren dai hon
    if (nxt[i + 1][0]) 
      cmax(dp[nxt[i + 1][0]][0], dp[i][0]);
    if (nxt[dp[i][0].se + 1][1]) 
      cmax(dp[nxt[dp[i][0].se + 1][1]][1], {dp[i][0].fi, i});
    if (nxt[i + 1][2])
      cmax(dp[nxt[i + 1][2]][0], {dp[i][0].fi, nxt[i + 1][2]});
    // hang duoi dai hon
    if (nxt[i + 1][1])
      cmax(dp[nxt[i + 1][1]][1], dp[i][1]);
    if (nxt[dp[i][1].se + 1][0])
      cmax(dp[nxt[dp[i][1].se + 1][0]][0], {dp[i][1].fi, i});
    if (nxt[i + 1][2])
      cmax(dp[nxt[i + 1][2]][1], {dp[i][1].fi, nxt[i + 1][2]});
  }
  int res = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < 2; ++j)
      res = max(res, dp[i][j].fi);
  cout << res;
	return 0;
}


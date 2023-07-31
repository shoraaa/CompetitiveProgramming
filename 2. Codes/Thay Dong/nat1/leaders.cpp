#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 50;

ll sum[N]; int val[N];
vector<int> a[N]; 
int n, m;

#define First(x) (__builtin_ffs(x) - 1)
int dp[1 << 15][N][N];

int call(int mask, int first, int last) {
  if (dp[mask][first][last]) 
    return dp[mask][first][last];
  int not_selected = ~mask & ((1 << n) - 1);
  int res = 1e9;
  // end vong qua vong khac
  if (sum[first] - val[first] <= val[last]) {
    if (!not_selected) return dp[mask][first][last] = 0;
    int i = First(not_selected);
    for (int j : a[i]) 
      res = min(res, call(mask | (1 << i), j, j) + val[j]);
  }
  // di tiep vong nay
  for (int msk = not_selected; msk;) {
    int i = First(msk); msk ^= 1 << i;
    for (int j : a[i]) if (sum[j] - val[j] <= val[last])
      res = min(res, call(mask | (1 << i), first, j) + val[j]);
  }
  return dp[mask][first][last] = res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; int id = 0;
  for (int i = 0, k; i < n; ++i) {
    cin >> k; a[i].resize(k);
    ll cur = 0;
    for (int j = 0; j < k; ++j)
      a[i][j] = id++, cin >> val[id-1], cur += val[id-1];
    for (int j = 0; j < k; ++j) sum[a[i][j]] = cur;
      
  }

  int res = 1e9;
  for (int j : a[0])
    res = min(res, call(1 << 0, j, j) + val[j]);
  cout << (res == 1e9 ? -1 : res);
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5, inf = 1e9;
int a[N], b[N], c[2 * N];
int n, m;
void task2() {
  int res = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] > b[0]) continue;
    int j = i, flag = 0;
    while (j < n && a[j] <= b[0]) 
      flag |= a[j] == b[0], j++;
    if (flag) res += j - i;
    i = j - 1; 
  }
  cout << res;
}
int pos[N], spt[N][20];
int get(int l, int r) {
  if (l > r) swap(l, r);
  int k = __lg(r - l + 1);
  return max(spt[l][k], spt[r-(1<<k)+1][k]);
}
void task3() {
  memset(pos, -1, sizeof(pos));
  for (int i = 0; i < n; ++i)
    pos[a[i]] = i;
  vector<int> dp(n + 1, inf); dp[0] = -inf;
  int res = 0;
  for (int i = 0; i < n; ++i) if (~pos[b[i]] && get(i, pos[b[i]]) == b[i]) {
    int k = upper_bound(dp.begin(), dp.end(), pos[b[i]]) - dp.begin();
    res = max(res, k), dp[k] = pos[b[i]];
  }
  cout << res;
}
int dp[5005][5005];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)  
    cin >> a[i], c[i] = a[i];
  for (int i = 0; i < n; ++i)
    cin >> b[i], c[i + n] = b[i];
  sort(c, c + n*2);
  m = unique(c, c + n*2) - c;
  for (int i = 0; i < n; ++i)
    a[i] = lower_bound(c, c + m, a[i]) - c,
    b[i] = lower_bound(c, c + m, b[i]) - c,
    spt[i][0] = a[i];
  for (int j = 1; j < 17; ++j)
    for (int i = 0; i + (1 << j) - 1 < n; ++i)
      spt[i][j] = max(spt[i][j-1], spt[i+(1<<(j-1))][j-1]);
  int ftask2 = 1;
  for (int i = 1; i < n; ++i) 
    ftask2 &= b[i] == b[i-1];
  if (ftask2) return task2(), 0;
  else if (n > 5000) return task3(), 0;
  dp[0][0] = 0; int res = 0;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    if (get(i-1, j-1) == b[i-1]) 
      dp[i][j] = max(dp[i][j], dp[i-1][j] + 1);
  }
  cout << dp[n][n];
	return 0;
}


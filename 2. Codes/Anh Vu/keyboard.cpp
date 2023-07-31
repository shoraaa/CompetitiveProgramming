#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define bit(msk, i) ((msk) >> (i) & 1)
const int N = 1e5 + 5;
const ll inf = 1e16;
int n, m;
string s;
int cnt[20][20];
ll cost[20][1 << 20], dp[1 << 20];
ll call(int msk) {
  if (__builtin_popcount(msk) == m)
    return 0;
  if (~dp[msk])
    return dp[msk];
  ll res = inf, val = 0;
  for (int i = 0; i < m; ++i) if (!bit(msk, i))
    val += cost[i][msk],
    res = min(res, call(msk | (1 << i)));
  return dp[msk] = res + val;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> s;
  for (int i = 1; i < n; ++i)
    cnt[s[i] - 'a'][s[i-1] - 'a']++;

  for (int c = 0; c < m; ++c) for (int msk = 1; msk < 1 << m; ++msk) {
    int i = __builtin_ctz(msk);
    cost[c][msk] = cost[c][msk ^ (1 << i)] + cnt[c][i] + cnt[i][c];
  }
      
  memset(dp, -1, sizeof(dp));
  cout << call(0);
	return 0;
}


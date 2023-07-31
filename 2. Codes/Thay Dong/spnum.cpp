#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int dp[905][8105], to[905][8105];
void solve() {
  int s, p; cin >> s >> p;
  if (s > 900 || p > 8100 || !~dp[s][p])
    return cout << "No solution\n", void();
  int val = dp[s][p]; string res;
  while (s && p) {
    int d = to[s][p];
    s -= d, p -= d*d, res += d + '0';
  }
  reverse(res.begin(), res.end());
  if (res.empty()) cout << 0 << '\n';
  else cout << res << '\n';
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  queue<pair<int, int>> q;
  memset(dp, -1, sizeof(dp));
  dp[0][0] = 0; q.emplace(0, 0);
  while (!q.empty()) {
    auto t = q.front(); q.pop();
    int s = t.first, p = t.second;
    if (dp[s][p] == 100) break;
    for (int d = 0; d <= 9; ++d) if (!~dp[s + d][p + d*d])
      dp[s + d][p + d*d] = dp[s][p] + 1,
      to[s + d][p + d*d] = d,
      q.emplace(s + d, p + d*d);
  }
  int T; cin >> T;
  while (T--) 
    solve();
	return 0;
}


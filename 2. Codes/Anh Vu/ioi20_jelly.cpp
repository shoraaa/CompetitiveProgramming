#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e3 + 5, M = 1e4 + 5;
using ii = pair<int, int>;
ii a[N], dp[N][M];
ii best(ii& u, ii& v) {
  if (u.first == v.first) return u.second < v.second ? u : v;
  return u.first > v.first ? u : v;
}
int n, X, Y;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> X >> Y;
  for (int i = 1; i <= n; ++i)
    cin >> a[i].first >> a[i].second;
  sort(a + 1, a + n + 1, [&](ii& u, ii& v) {
    return u.second < v.second;
  });
  for (int x = 0; x <= X; ++x)
    dp[0][x] = {0, 0};
  for (int i = 1; i <= n; ++i) for (int x = 0; x <= X; ++x) {
    dp[i][x] = dp[i-1][x];
    if (x >= a[i].first) {
      auto p = dp[i-1][x-a[i].first]; p.first++;
      dp[i][x] = best(dp[i][x], p);
    }
    if (dp[i-1][x].second + a[i].second <= Y) {
      auto p = dp[i-1][x]; p.first++; p.second += a[i].second;
      dp[i][x] = best(dp[i][x], p);
    }
  }
  cout << dp[n][X].first;
	return 0;
}


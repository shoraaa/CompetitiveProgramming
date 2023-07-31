#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e2 + 5, X = 1e6 + 5;
int val[X];
int n, S;
vector<pair<int, int>> pos;
vector<int> c;
int dp[N][N][N];
int call(int l, int r, int h) {
  if (h == c.size()) return 0;
  if (~dp[l][r][h]) return dp[l][r][h];
  int flag = 0;
  for (int i = l; i <= r; ++i)
    if (pos[i].second == h) { flag = 1; break; }
  if (flag) {
    int res = 1e9;
    for (int m = h; m < c.size(); ++m)
      if (ll(pos[r].first - pos[l].first) * c[m] <= S)
        res = min(res, call(l, r, m+1) + 1);
    for (int m = l; m < r; ++m)
      res = min(res, call(l, m, h) + call(m+1, r, h));
    return dp[l][r][h] = res;
  } 
  return dp[l][r][h] = call(l, r, h+1);
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("rectcover.in", "r"))
    freopen("rectcover.in", "r", stdin),
    freopen("rectcover.out", "w", stdout);
  cin >> n >> S; int max_x = 0;
  for (int i = 0, x, y; i < n; ++i) 
    cin >> x >> y, 
    val[x] = max(val[x], y),
    max_x = max(max_x, x);
  for (int x = 0; x <= max_x; ++x) 
    if (val[x]) pos.emplace_back(x, val[x]), c.emplace_back(val[x]);
  sort(c.begin(), c.end());
  c.erase(unique(c.begin(), c.end()), c.end());
  for (auto& p : pos) 
    p.second = lower_bound(c.begin(), c.end(), p.second) - c.begin();
  memset(dp, -1, sizeof(dp));
  cout << call(0, pos.size() - 1, 0);
	return 0;
}


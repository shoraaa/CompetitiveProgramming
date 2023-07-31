#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 5, M = 1e5 + 5;
int n, T, m;
int bit[M];
int get(int x) {
  int res = 0;
  for (; x; x -= x & -x)
    res = max(res, bit[x]);
  return res;
}
void update(int x, int v) {
  for (; x <= m; x += x & -x)
    bit[x] = max(bit[x], v);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> T;
  vector<int> a(n); 
  for (int& x : a) cin >> x;
  vector<int> c = a;
  sort(c.begin(), c.end());
  c.erase(unique(c.begin(), c.end()), c.end());
  m = c.size();
  for (int& x : a) x = lower_bound(c.begin(), c.end(), x) - c.begin() + 1;
  vector<int> dp(m+1);
  int res = 0; vector<int> last;
  while (T--) {
    vector<int> old = dp;
    for (int x : a) {
      dp[x] = get(x) + 1;
      update(x, dp[x]);
    }
    vector<int> cur(m+1);
    for (int x = 1; x <= m; ++x)
      cur[x] = dp[x] - old[x];
    if (cur == last) {
      for (int x = 1; x <= m; ++x)
        dp[x] += cur[x] * T;
      break;
    }
    cur.swap(last);
  }
  for (int x = 1; x <= m; ++x)
    res = max(res, dp[x]);
  cout << res;
	return 0;
}


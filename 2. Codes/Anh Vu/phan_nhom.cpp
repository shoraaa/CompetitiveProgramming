#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
int a[N];
ll dp[N][2];
int n;
int cost(int i, int j) {
  if (i > j) return 0;
  return max(a[i], a[j]) - min(a[i], a[j]);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  if (n == 1)
    return cout << 0, 0;
  vector<int> d;
  d.emplace_back(0);
  for (int i = 1; i < n-1; ++i)
    if (a[i] >= max(a[i-1], a[i+1]) || a[i] <= min(a[i-1], a[i+1]))
      d.emplace_back(i);
  d.emplace_back(n-1);
  int m = d.size();
  dp[0][1] = cost(0, d[0]);
  dp[0][0] = cost(0, d[0] - 1);
  for (int i = 1; i < m; ++i) {
    dp[i][1] = max(dp[i-1][0] + cost(d[i-1], d[i]),
                   dp[i-1][1] + cost(d[i-1] + 1, d[i]));
    dp[i][0] = max(dp[i-1][0] + cost(d[i-1], d[i] - 1),
                   dp[i-1][1] + cost(d[i-1] + 1, d[i] - 1));
  }
  cout << max(dp[m-1][0], dp[m-1][1]);
	return 0;
}


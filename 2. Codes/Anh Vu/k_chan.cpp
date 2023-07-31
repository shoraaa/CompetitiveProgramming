#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
int chan[N], le[N], dp[N][2];
int n, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0, x; i < n; ++i) { 
    cin >> x;
    if (x & 1) le[i % k]++;
    else chan[i % k]++;
  }
  dp[0][0] = le[0], dp[0][1] = chan[0];
  for (int i = 1; i < k; ++i) {
    dp[i][0] = min(dp[i-1][0] + le[i], dp[i-1][1] + chan[i]);
    dp[i][1] = min(dp[i-1][0] + chan[i], dp[i-1][1] + le[i]);
  }
  cout << dp[k-1][0];
	return 0;
}


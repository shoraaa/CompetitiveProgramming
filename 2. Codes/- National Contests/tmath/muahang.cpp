#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
int dp[N];
int a, b, c;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  // Ax + By = C
  int T;
  cin >> T;
  while (T--) {
    cin >> a >> b >> c;
    dp[0] = 1;
    for (int i = 1; i <= c; ++i) {
      dp[i] = 0;
      if (i >= a) dp[i] |= dp[i - a];
      if (i >= b) dp[i] |= dp[i - b];
    }
    cout << (dp[c] ? "Yes\n" : "No\n");
  }
	return 0;
}


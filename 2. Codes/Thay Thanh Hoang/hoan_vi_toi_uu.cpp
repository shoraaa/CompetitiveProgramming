#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5005, INF = 1e9;
int dp[N];
int a[N];
int n, w;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> w;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  sort(a, a + n);
  // fw = max (MIN) cua tap (a/P) ma P = w
  memset(dp, -1, sizeof(dp));
  dp[0] = 0;
  for (int i = n - 1; ~i; --i) {
    for (int j = w; ~j; --j) {
      if (j >= a[i] && ~dp[j - a[i]]) {
        if (~dp[j]) dp[j] = max(a[i], dp[j - a[i]]);
        else dp[j] = dp[j - a[i]];
      } else if (~dp[j]) {
        dp[j] = a[i];
      }
    }
  }
  for (int i = 0; i <= w; ++i) if (dp[i] == 0 || dp[i] > w - i) 
    return cout << w - i, 0;
	return 0;
}


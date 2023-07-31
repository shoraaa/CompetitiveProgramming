#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int cmax(int& x, int y) {
  return x < y ? x = y, 1 : 0;
}

const int N = 3e4, S = 500;

int dp[N+1][2 * S + 5];

int a[N];
int n, d;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> d;
  for (int i = 0, p; i < n; ++i)
    cin >> p, a[p]++;
  memset(dp, -1, sizeof(dp));
  dp[d][0+S] = a[d]; int res = 0;
  for (int i = 0; i < N; ++i) for (int j = -S; j < S; ++j) if (~dp[i][j+S]) {
    int l = d + j; cmax(res, dp[i][j+S]);
    if (i+l-1 <= N && l > 0) cmax(dp[i+l-1][j-1+S], dp[i][j+S] + a[i+l-1]);
    if (i+l <= N) cmax(dp[i+l][j+S], dp[i][j+S] + a[i+l]);
    if (i+l+1 <= N) cmax(dp[i+l+1][j+1+S], dp[i][j+S] + a[i+l+1]);
  }
  cout << res;
	return 0;
}


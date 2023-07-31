#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e6 + 6, inf = 1e9;
int cnt[N];
vector<int> dp[N], suf[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
  	cin >> n;
  	int deleted = 0;
  	memset(cnt, 0, sizeof(cnt));
    for (int i = 0, x; i < n; ++i) {
      cin >> x;
      if (x > n * 2) deleted++;
      else cnt[x]++;
    }
    dp[0].resize(n*2+5), suf[0].resize(n*2+5);
    for (int x = 1; x <= n * 2; ++x)
      dp[x].assign(n*2/x+5, 0), 
      suf[x].assign(dp[x].size(), inf);
    for (int x = 1; x <= n * 2; ++x) 
      for (int y = n*2/x+1; ~y; --y) 
        dp[x][y] = abs(cnt[x] - y) + suf[x-1][y],
        suf[x][y] = min(suf[x][y+1], dp[x][y]);
    cout << min(dp[n*2][0], dp[n*2][1]) + deleted << '\n';
  }
	return 0;
}


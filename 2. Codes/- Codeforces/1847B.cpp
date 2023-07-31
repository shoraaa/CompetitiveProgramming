#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5, INF = 1e9;
int a[N], last_0[30], dp[N], max_dp[N], pre[N];
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    
    pre[1] = a[1];
    for (int i = 2; i <= n; ++i) {
      pre[i] = pre[i - 1] & a[i];
    }
    if (pre[n] > 0) {
      cout << 1 << '\n';
      continue;
    }
    
    for (int i = 0; i <= 29; ++i) last_0[i] = INF;
    
    dp[0] = 0;
    
    for (int i = 1; i <= n; ++i) {
      
      for (int j = 0; j <= 29; ++j) {
        if (!(a[i] & (1 << j))) last_0[j] = i;
      }
      
      if (pre[i] > 0) {
        dp[i] = -INF;
        max_dp[i] = max(max_dp[i - 1], dp[i]);
        continue;
      }
      
      dp[i] = 1;
      
      int pos = i;
      for (int j = 0; j <= 29; ++j) {
        pos = min(pos, last_0[j]);
      }
      
      dp[i] = max(dp[i], max_dp[pos - 1] + 1);
      
      max_dp[i] = max(max_dp[i - 1], dp[i]);
      
    }
    
    cout << dp[n] << '\n';
    
    
  }
	return 0;
}


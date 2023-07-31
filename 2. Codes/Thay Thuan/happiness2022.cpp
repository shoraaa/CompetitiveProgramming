#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 20;
int a[N], b[N];
ll dp1[1 << N], dp2[1 << N], dp[1 << N];
int n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> n >> m;
    
    for (int i = 0; i < n; ++i)   
      cin >> a[i];
    for (int i = 0; i < n; ++i)   
      cin >> b[i];
      
    for (int msk = 0; msk < 1 << n; ++msk) {
      ll sum1 = 0, sum2 = 0;
      for (int i = 0; i < n; ++i) 
        if (msk >> i & 1) sum1 += a[i], sum2 += b[i];
      dp1[msk] = sum1 >= m; dp2[msk] = sum2 >= m;
    }
    
    for (int i = 0; i < n; ++i)
      for (int msk = 0; msk < 1 << n; ++msk) if (msk >> i & 1)
        dp1[msk] += dp1[msk ^ (1 << i)],
        dp2[msk] += dp2[msk ^ (1 << i)];
        
    for (int msk = 0; msk < 1 << n; ++msk)
      dp[msk] = dp1[msk] * dp2[msk];
      
    for (int i = 0; i < n; ++i)
      for (int msk = 0; msk < 1 << n; ++msk) if (msk >> i & 1)
        dp[msk] -= dp[msk ^ (1 << i)];
    
    cout << dp[(1 << n) - 1] << '\n';
  }
	return 0;
}


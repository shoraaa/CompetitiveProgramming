#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e2 + 5, M = 998244353;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
int n;
int a[N], f[N], dp[N * N][N];
ll fac[N];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; fac[0] = 1;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], 
    f[i] = f[i-1] + a[i], 
    fac[i] = fac[i-1] * i % M;
  if (f[n] & 1)
    return cout << 0, 0;
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i) for (int s = f[i-1]; s >= 0; --s) 
    for (int j = 0; j < i; ++j) if (dp[s][j]) {
      add(dp[s+a[i]][j+1], dp[s][j]);
    }
  int res = 0;
  for (int i = 1; i < n; ++i) 
    add(res, fac[i] * fac[n-i] % M * dp[f[n] / 2][i] % M);
  cout << res;
	return 0;
}


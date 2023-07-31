#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5005, M = 1e9 + 7;
int n; ll k;
int dp[N], C[N][N];

void add(int& x, int y) { x += y; if (x >= M) x -= M; }

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k; 
  
  C[0][0] = 1;
  for (int i = 1; i <= n; ++i) for (int j = 0; j <= n; ++j) {
    C[i][j] = C[i - 1][j];
    if (j) add(C[i][j], C[i - 1][j - 1]);
  }
  
  dp[1] = 1;
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= i - 1; ++j) if (1LL * j * (n - j) <= k)
      add(dp[i], 1LL * dp[j] * C[i - 2][j - 1] % M * j % M * dp[i - j] % M);
  }
  cout << dp[n];
	return 0;
}


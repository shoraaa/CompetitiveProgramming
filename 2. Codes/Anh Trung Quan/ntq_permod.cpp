#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5, M = 1e9 + 7;
void add(int& x, int y) { 
  x += y; if (x >= M) x -= M;
}
int n, k;

namespace task1 {
  int dp[1 << 16][16];
  void solve() {
    dp[1][0] = 1;
    for (int msk = 1; msk < 1 << n; ++msk) for (int i = 0; i < n; ++i) {
      if (!dp[msk][i]) continue;
      for (int j = 0; j < n; ++j) if (!(msk >> j & 1)) {
        if ((i + 1) % (j + 1) > k) continue;
        add(dp[msk ^ (1 << j)][j], dp[msk][i]);
      }
    }
    int res = 0;
    for (int i = 0; i < n; ++i)
      add(res, dp[(1 << n) - 1][i]);
    cout << 1LL * res * n % M; exit(0);
  }
};

int dp[N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  if (n <= 16) task1::solve();
  if (k == 1) return cout << n, 0;
  
  dp[3] = 2;
  int res = 0;
  for (int i = 3; i <= n; ++i) {
    add(res, dp[i]);
    for (int j = i - 1; j <= n; j += i - 1) {
      if (j != i - 1) add(dp[j], dp[i]);
      if (j != i - 1) add(dp[j + 1], dp[i]);
      if (i - 1 != 2) add(dp[j + 2], dp[i]);
    }
  }
  cout << 1LL * res * n % M;
  
	return 0;
}


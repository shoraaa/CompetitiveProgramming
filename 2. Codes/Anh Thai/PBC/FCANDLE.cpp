#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5005, M = 1e9;
int dp[N], C[N][N];

void add(int& x, int y) { x += y; if (x >= M) x -= M; }

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  
  C[0][0] = 1;
  for (int i = 1; i < N; ++i) for (int j = 0; j < N; ++j) {
    C[i][j] = C[i - 1][j];
    if (j) add(C[i][j], C[i - 1][j - 1]);
  }
  
  dp[0] = 1, dp[1] = 1;
  for (int i = 2; i < N; ++i) {
    for (int k = 0; k <= i - 2; ++k) 
      add(dp[i], 1LL * C[i - 2][k] * dp[k] % M * dp[i - k - 1] % M);
  }
  int T; cin >> T;
  while (T--) {
    int n; cin >> n;
    string s = to_string(dp[n]);
    while (s.size() < 9) s = '0' + s;
    cout << s << '\n';
  }
	return 0;
}


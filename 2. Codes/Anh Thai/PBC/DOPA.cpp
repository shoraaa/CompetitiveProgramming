#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, M = 1e9 + 7;
void add(int& x, int y) { x += y; if (x >= M) x -= M; }
void sub(int& x, int y) { x -= y; if (x < 0) x += M; }
int dp[N], pw[N];
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  pw[0] = 1;
  for (int i = 1; i <= n; ++i)
    pw[i] = pw[i - 1] * 26LL % M;
  // dp[i] = so xau kep chi co 1 cach cat do dai i
  for (int i = 1; i <= n; ++i) {
    //for (int k = 0; k <= i - 1; ++k) add(dp[i], 1LL * pw[(k+1)/2] * pw[(i-k+1)/2] % M);
    
    if (i % 2 == 0) {
      add(dp[i], 1LL * pw[i / 2] * (i / 2) % M);
      add(dp[i], 1LL * pw[i / 2 + 1] * (i / 2) % M);
    } else {
      add(dp[i], 1LL * pw[(i + 1) / 2] * i % M);
    }
    
    
    for (int k = 1; k * k <= i; ++k) if (i % k == 0) {
      if (k != 1) sub(dp[i], 1LL * dp[i / k] * k % M);
      if (k * k != i) sub(dp[i], dp[k] * ll(i / k) % M);
    } 
  }
  int res = 0;
  for (int k = 1; k <= n; ++k) 
    add(res, dp[k] * ll(n / k) % M);
  cout << res;
	return 0;
}


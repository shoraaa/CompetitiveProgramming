#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5, M = 1e9 + 7;
int dp[N];
int n;

int call(int i) {
  if (i == n) return 1;
  if (i == n-1) return 1;
  if (dp[i]) return dp[i];
  return dp[i] = (call(i + 1) + 1LL * call(i + 2) * (n - i - 1) % M) % M;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("dinner.inp", "r"))
    freopen("dinner.inp", "r", stdin),
    freopen("dinner.out", "w", stdout);
    
  int T; cin >> T;
  while (T--) { 
    cin >> n; 
    memset(dp, 0, sizeof(dp));
    cout << call(1) << '\n';
  }

	return 0;
}


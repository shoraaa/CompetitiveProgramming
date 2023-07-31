#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll n;
vector<ll> d;
int dp[7005][7005];

int call(int i, int j) {
  if (i == j) return 1;
  if (~dp[i][j]) return dp[i][j];
  int res = 1; 
  for (int k = i, k2 = j-1; d[k]*d[k] <= d[j]; ++k) {
    if (d[j] % d[k] == 0) {
      ll val = d[j] / d[k];
      while (d[k2] > val) k2--;
      res += call(k, k2);
    }
  }
  return dp[i][j] = res;
}

int main() {
  if (fopen("factor.inp", "r")) 
    freopen("factor.inp", "r", stdin),
    freopen("factor.out", "w", stdout);
  int T; cin >> T;
  while (T--) {
    cin >> n; d.clear();
    for (ll i = 1; i * i <= n; ++i) if (n % i == 0) {
      d.emplace_back(i);
      if (i * i < n) d.emplace_back(n / i);
    }
    sort(d.begin(), d.end());
    memset(dp, -1, sizeof(int) * (7005 * (d.size() + 1)));
    cout << call(1, d.size() - 1) - 1 << '\n'; 
  }
	return 0;
}


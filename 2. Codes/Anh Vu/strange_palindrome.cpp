#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 5;
const int M = 111539786;
int nxt[N][2];
ll dp[N][N];
string s;
int n;
ll calc(int k) {
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j <= k; ++j) {
      dp[i][j] %= M;
      if (j + 1 <= k) dp[nxt[i][0]][j + 1] += dp[i][j];
      if (j - 1 >= 0) dp[nxt[i][1]][j - 1] += dp[i][j];
    }
  ll res = 0;
  for (int i = 1; i <= n; ++i)
    res += dp[i][0] % M;
  return res % M;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	int k;
  cin >> s >> k;
  n = s.size();
  s = ' ' + s;
  nxt[n + 1][0] = nxt[n + 1][1] = n + 1;
  for (int i = n; ~i; --i) {
    nxt[i][0] = nxt[i + 1][0];
    if (s[i + 1] == '(') nxt[i][0] = i + 1;
    nxt[i][1] = nxt[i + 1][1];
    if (s[i + 1] == ')') nxt[i][1] = i + 1;
  }
  cout << (((calc(k) - calc(k-1)) % M) + M) % M;
	return 0;
}


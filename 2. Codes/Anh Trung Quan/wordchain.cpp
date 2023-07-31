#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int a[2][30], dp[2][30];
int n, m;

int call(int c, int t) {
  if (!a[t][c]) return 0;
  if (~dp[t][c]) return dp[t][c];
  if (a[t][c] <= a[t^1][c]) return dp[t][c] = call(c+1, t) && !call(c+1, t^1);
  else return dp[t][c] = !call(c+1, t^1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("wordchain.inp", "r"))
    freopen("wordchain.inp", "r", stdin),
    freopen("wordchain.out", "w", stdout);
  cin >> n >> m; string s;
  for (int i = 0; i < n; ++i)
    cin >> s, a[0][s[0] - 'a' + 1]++;
  for (int i = 0; i < m; ++i)
    cin >> s, a[1][s[0] - 'a' + 1]++;
  memset(dp, -1, sizeof(dp));
  int i = 0; while (!a[0][i]) i++;
  cout << (call(i, 0) ? "qb" : "hv");
	return 0;
}


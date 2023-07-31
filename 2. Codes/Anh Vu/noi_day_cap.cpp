#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e2 + 5, M = 1e9 + 7;
void add(int& x, int y) { x += y; if (x >= M) x -= M; }
int sum(int x, int y) { x += y; if (x >= M) x -= M; return x; }
int mul(ll x, ll y) { return x * y % M; }
int n;
int a[N], c[N][N], dp[N][N][2];
int call(int l, int r);
int call(int l, int r, int tp) {
  if (l > r) return 0;
  if (l == r) return !tp;
  if (tp && !c[l][r]) return 0;
  if (r-l==1) return tp && c[l][r];
  if (~dp[l][r][tp]) return dp[l][r][tp];
  int res = 0;
  if (tp == 0) {
    for (int i = l+1; i < r; ++i) 
      add(res, mul(call(l, i, 1), call(i, r)));
  } else {
    for (int i = l; i < r; ++i) 
      add(res, mul(call(l, i), call(i+1, r)));
  }
  return dp[l][r][tp] = res;
}
int call(int l, int r) {
  return sum(call(l, r, 0), call(l, r, 1));
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j)
    c[i][j] = c[j][i] = __gcd(a[i], a[j]) > 1;
  memset(dp, -1, sizeof(dp));
  cout << call(0, n-1);
	return 0;
}


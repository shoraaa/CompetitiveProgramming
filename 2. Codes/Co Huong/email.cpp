#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 55;
int dp[N][N], a[N];
int n, m = 0;

int call(int l, int r) {
  if (l >= r) return 0;
  if (~dp[l][r]) return dp[l][r];
  int res = 0;
  if (a[l] == a[r]) res = max(res, call(l + 1, r - 1) + 1);
  for (int i = l + 1; i < r; ++i) 
    res = max(res, call(l, i) + call(i, r));
  return dp[l][r] = res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("email.inp", "r")) 
    freopen("email.inp", "r", stdin),
    freopen("email.out", "w", stdout);
  cin >> n;
  for (int i = 0, x; i < n; ++i) {
    cin >> x;
    if (m == 0 || x != a[m-1]) a[m++] = x;
  }
  memset(dp, -1, sizeof(dp));
  cout << m - call(0, m-1);
	return 0;
}


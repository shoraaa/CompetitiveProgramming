#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 55, L = 10005, M = 1e9 + 7;
ll dp[N][N][L], a[N];

void add(ll& x, int y) {
  x += y; if (x >= M) x -= M;
}

int n, m;
ll fac[L];
ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

ll C(int n, int k) {
  return fac[n] * pw(fac[k], M - 2) % M * pw(fac[n - k], M - 2) % M;
}

ll euler(int n, int m) {
  return C(n + m - 1, n - 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) 
    cin >> a[i];
  sort(a, a + n);
  dp[1][1][1] = 1;
  for (int i = 1; i < n; ++i) for (int j = 1; j < n; ++j) for (int k = 1; k <= m; ++k) {
    if (!dp[i][j][k]) continue;
    // dat thang a[i + 1] vao 
    // nhom moi
    add(dp[i + 1][j + 1][k + 1], dp[i][j][k] * (j + 1) % M);
    // mo rong nhom cu
    if (k + a[i] <= m)
      add(dp[i + 1][j][k + a[i]], dp[i][j][k] * j * 2 % M);
    // gop 2 nhom cu
    if (k + (a[i] * 2 - 1) <= m)
      add(dp[i + 1][j - 1][k + (a[i] * 2 - 1)], dp[i][j][k] * (j - 1) % M);
  }
  
  fac[0] = 1;
  for (int i = 1; i < L; ++i)
    fac[i] = fac[i - 1] * i % M;
  
  ll res = 0;
  for (int k = 1; k <= m; ++k) if (dp[n][1][k])
    add(res, dp[n][1][k] * euler(n + 1, m - k) % M);
  cout << res;
	return 0;
}


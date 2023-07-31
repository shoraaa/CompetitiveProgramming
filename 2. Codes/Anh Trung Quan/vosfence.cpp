#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 105, M = 1e9 + 7;
int dp1[N][N][2*N][2], dp2[N][N*2], dp3[N][N*2];
int n, w, b, r, k, m;

void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

ll fac[N*3], inv[N*3];
ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * inv[k] % M * inv[n-k] % M;
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  
  fac[0] = inv[0] = 1;
  for (int i = 1; i < N*3; ++i)
    fac[i] = fac[i-1] * i % M, inv[i] = pw(fac[i], M-2);
  
  cin >> w >> b >> r >> k >> m; n = w + b + r;
  
  dp1[1][0][0][0] = dp1[0][1][0][1] = 1;
  for (int i = 0; i <= r; ++i) for (int j = 0; j <= b; ++j) for (int p = 0; p <= r+b-1; ++p) {
    add(dp1[i + 1][j][p][0], dp1[i][j][p][0]);
    add(dp1[i][j + 1][p + 1][1], dp1[i][j][p][0]);
    add(dp1[i][j + 1][p][1], dp1[i][j][p][1]);
    add(dp1[i + 1][j][p + 1][0], dp1[i][j][p][1]);
  }
  for (int p = 0; p <= r+b-1; ++p)
    add(dp1[r][b][p][0], dp1[r][b][p][1]);
  
  for (int i = 0; i <= r+b+1; ++i) dp2[0][i] = 1;
  for (int i = 1; i <= w; ++i) for (int j = 1; j <= r+b+1; ++j) 
    for (int p = 0; p < k && i-p>=0; ++p) add(dp2[i][j], dp2[i-p][j-1]);
    
  dp3[0][0] = 1;
  for (int i = 1; i <= w; ++i) for (int j = 1; j <= r+b+1; ++j) 
    for (int p = 1; p < k && i-p>=0; ++p) add(dp3[i][j], dp3[i-p][j-1]);
  
  //for j vi tri, co r+b+1-j vi tri de nhet luong ko am vao, j-m vi tri nhet luong duong vao
  int res = 0;
  for (int i = m; i < r+b; ++i) for (int j = 0; j <= w; ++j) 
    add(res, ll(dp1[r][b][i][0]) * dp2[j][r+b+1-i] % M * dp3[w-j][i-m] % M * C(i, i-m) % M);
  
  cout << res;
	return 0;
}

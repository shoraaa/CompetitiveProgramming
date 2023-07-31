#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 239;

using T = int;
#define Matrix vector<vector<T>> 
Matrix mul(Matrix& a, Matrix& b) {
  Matrix c(a.size(), vector<T>(b[0].size()));
  for (int i = 0; i < a.size(); ++i) for (int j = 0; j < b[0].size(); ++j)
    for (int k = 0; k < a[0].size(); ++k) {
      c[i][j] += a[i][k] * b[k][j] % M;
      if (c[i][j] >= M) c[i][j] -= M;
    }
  return c;
}

Matrix pw(Matrix x, ll k) {
  Matrix res(x.size(), vector<T>(x.size()));
  for (int i = 0; i < x.size(); ++i) res[i][i] = 1;
  for (; k; k >>= 1, x = mul(x, x))
    if (k & 1) res = mul(res, x);
  return res;
}

int c[M + 5][31][31], f[2][31];
ll n; int m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i <= m; ++i) c[1][i][i] = 1;
  for (int i = 2; i <= M + 1; ++i) for (int j = 1; j <= m; ++j) for (int k = 1; k <= m; ++k) {
    c[i][j][k] = c[i - 1][j][k] * j * 2 % M + c[i - 1][j - 1][k] * (i - 2 * (j - 1)) % M;
    if (c[i][j][k] >= M) c[i][j][k] -= M; 
  }
  Matrix G(31, vector<T>(31));
  for (int i = 0; i <= m; ++i) 
    for (int j = 0; j <= m; ++j)
      G[j][i] = c[M + 1][i][j];
  G = pw(G, (n - 1) / M);
  Matrix A(1, vector<T>(31));
  A[0][1] = 1;
  A = mul(A, G);
  for (ll i = M * ((n - 1) / M) + 2; i <= n; ++i) for (int j = m; j; --j) {
    A[0][j] = A[0][j] * j * 2 % M + A[0][j - 1] * (i - 2LL * (j - 1)) % M;
    if (A[0][j] >= M) A[0][j] -= M;
  }
  cout << A[0][m];
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

int n, M;

#define Matrix vector<vector<int>>
Matrix mul(Matrix a, Matrix b) {
  Matrix c(a.size(), vector<int>(b[0].size()));
  for (int i = 0; i < a.size(); ++i) for (int j = 0; j < b[0].size(); ++j) 
    for (int k = 0; k < b.size(); ++k) {
      c[i][j] += 1LL * a[i][k] * b[k][j] % M;
      if (c[i][j] < 0) c[i][j] += M;
      else if (c[i][j] >= M) c[i][j] -= M;
    }
  return c;
}
Matrix pw(Matrix x, int k) {
  Matrix res = {{1, 0}, {0, 1}};
  for (; k; k >>= 1, x = mul(x, x))
    if (k & 1) res = mul(res, x);
  return res;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  // f[i] = f[i - 2] + 2*f[i - 4] + 4*f[i-6] + .. + k*f[4]
  // f[i-2] = ..     +   f[i - 4] + 2*f[i-6] + .. + (k-1)*f[4]
  // f[i] = 2 * f[i-2] + f[i-4] + .. + f[4]
  // f[i - 2] = 2 * f[i-4] + f[i-6] + .. + f[4]
  // f[i] = 3*f[i-2] - f[i-4] -> MATRIX 
  cin >> n >> M;
  Matrix A = {{1, 2}}, B = {{0, -1}, {1, 3}};  
  cout << mul(A, pw(B, n - 2))[0][0];
	return 0;
}


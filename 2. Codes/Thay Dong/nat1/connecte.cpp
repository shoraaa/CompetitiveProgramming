#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9;

using T = int;
#define Matrix vector<vector<T>> 
Matrix mul(const Matrix& a, const Matrix& b) {
  Matrix c(a.size(), vector<T>(b[0].size()));
  for (int i = 0; i < a.size(); ++i) for (int j = 0; j < b[0].size(); ++j)
    for (int k = 0; k < a[0].size(); ++k) {
      c[i][j] += 1LL * a[i][k] * b[k][j] % M;
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

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int n; cin >> n;
  
  Matrix G = {{1, 1, 2, 1, 1, 1},
              {1, 1, 2, 1, 1, 1},
              {1, 1, 2, 1, 1, 1},
              {0, 0, 1, 0, 0, 0},
              {0, 0, 1, 0, 0, 0},
              {1, 1, 0, 0, 0, 0}};
               
  Matrix A = {{0, 0, 1, 1, 1, 0}};
  A = mul(A, pw(G, n - 2));
  int res = A[0][5] * 2;
  if (res >= M) res -= M;
  A = mul(A, G);
  res += A[0][5];
  if (res >= M) res -= M;
  cout << res;
  
	return 0;
}


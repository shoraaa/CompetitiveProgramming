#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

const int N = sqrt(7e9) + 5, B = 1e6;
int n; ll k, M;
ll a[20];
int lp[N];

ll mul(ll x, ll k) {
  ll res = 0;
  for (; k; k >>= 1, x = (x + x) % M)
    if (k & 1) res = (res + x) % M;
  return res;
}

#define Matrix vector<vector<ll>>
Matrix mul(Matrix a, Matrix b) {
  Matrix c(a.size(), vector<ll>(b[0].size()));
  for (int i = 0; i < a.size(); ++i) for (int j = 0; j < b[0].size(); ++j) 
    for (int k = 0; k < b.size(); ++k) {
      c[i][j] += mul(a[i][k], b[k][j]);
      if (c[i][j] < 0) c[i][j] += M;
      else if (c[i][j] >= M) c[i][j] -= M;
    }
  return c;
}
Matrix pw(Matrix x, ll k) {
  Matrix res(x.size(), vector<ll>(x.size()));
  for (int i = 0; i < x.size(); ++i) 
    res[i][i] = 1;
  for (; k; k >>= 1, x = mul(x, x))
    if (k & 1) res = mul(res, x);
  return res;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  
  vector<int> pr;
  for (int i = 2; i * i < N; ++i) if (!lp[i])
    for (int j = i * i; j < N; j += i) lp[j] = i;
  for (int i = 2; i < N; ++i) if (!lp[i]) pr.emplace_back(i);
  
  int T; cin >> T;
  while (T--) {
    cin >> n >> k >> M;
    for (int i = 0; i < n; ++i) 
      cin >> a[i];
    Matrix G(n + 1, vector<ll>(n + 1));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      if (a[j] % 6 != 1 && a[j] % 6 != 5) continue;
      ll val = a[i] * 6 + a[j];
      int flag = 0;
      for (int p : pr) {
        if (1LL * p * p > val) break;
        if (val % p == 0) {
          flag = 1; break;
        }
      }
      if (flag) continue;
      G[i][j] = 1;
    }
    G[n - 1][n] = 1;
    G[n][n] = 1;
    G = pw(G, k + 1);
    cout << G[0][n] << '\n';
     
  }
	return 0;
}


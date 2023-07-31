#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1005;
int f[N][N], alpha[N][N], beta[N][N], a[N][N];
int n, m, q;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("mab.inp", "r")) 
    freopen("mab.inp", "r", stdin),
    freopen("mab.out", "w", stdout);
  cin >> n >> m >> q;
  for (int i = 0; i < n; ++i) {
    vector<int> b(m);
    for (int j = 0; j < m; ++j)
      cin >> a[i][j], b[j] = a[i][j];
    sort(b.begin(), b.end());
    for (int j = 0; j < m; ++j)
      alpha[i][j] = lower_bound(b.begin(), b.end(), a[i][j]) - b.begin();
  }
  for (int j = 0; j < m; ++j) {
    vector<int> b(n);
    for (int i = 0; i < n; ++i)
      b[i] = a[i][j];
    sort(b.begin(), b.end());
    for (int i = 0; i < n; ++i)
      beta[i][j] = n - (upper_bound(b.begin(), b.end(), a[i][j]) - b.begin());
  }
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    f[alpha[i][j]][beta[i][j]]++;
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= m; ++j) {
    if (i > 0) f[i][j] += f[i - 1][j];
    if (j > 0) f[i][j] += f[i][j - 1];
    if (i > 0 && j > 0) f[i][j] -= f[i-1][j-1];
  }
  for (int i = 0, x, y; i < q; ++i) {
    cin >> x >> y; 
    cout << f[x][y] << '\n';
  }
	return 0;
}


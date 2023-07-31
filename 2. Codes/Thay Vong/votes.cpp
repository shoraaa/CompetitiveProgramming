/*
 * Author :  shora
 */
#include <bits/stdc++.h>
#define print(_v) for (auto &_ : _v) {cerr << _ << ' ';} cerr << endl;
using namespace std;
using ll = long long;
const int oo = 1e9;
const int N = 500;
int a[N*2 + 1][N*2 + 1], f[N*2+1][N*2+1];
int n, m;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
  	for (int j = 1; j <= m; ++j)
  		cin >> a[i][j];
  for (int i = 1; i <= n; ++i)
  	for (int j = m+1; j <= 2*m; ++j)
  		a[i][j] = a[i][j-m];
  for (int i = n+1; i <= 2*n; ++i)
  	for (int j = 1; j <= m; ++j)
  		a[i][j] = a[i-n][j];
  for (int i = n+1; i <= 2*n; ++i)
  	for (int j = m+1; j <= 2*m; ++j)
  		a[i][j] = a[i-n][j-m];
  for (int i = 1; i <= 2*n; ++i)
  	for (int j = 1; j <= 2*m; ++j)
  		f[i][j] = f[i-1][j] + f[i][j-1] - f[i-1][j-1] + a[i][j];
  int q;
  cin >> q;
  int R = 0, D = 0;
  int t, x, y, u, v;
  while (q--) {
  	cin >> t;
  	if (t == 0) {
  		cin >> x >> y;
  		R = (R + x) % m;
  		D = (D + y) % n;
		} else {
			cin >> x >> y >> u >> v;
			x += D; u += D;
			y += R; v += R;
			cout << f[u][v] - f[u][y-1] - f[x-1][v] + f[x-1][y-1] << '\n';
		}
	}
  return 0;
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
vector<vector<int>> a, b, c, d;
int r1[N], c1[N], r2[N], c2[N], val[N];
int n, m, q;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  a.resize(n + 2, vector<int>(m + 2)); b = a, c = a, d = a;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
    cin >> a[i][j];
  cin >> q;
  for (int i = 0; i < q; ++i)
    cin >> r1[i] >> c1[i] >> r2[i] >> c2[i] >> val[i],
    b[r1[i]][c1[i]] += val[i],
    b[r1[i]][c2[i] + 1] -= val[i],
    b[r2[i] + 1][c1[i]] -= val[i],
    b[r2[i] + 1][c2[i] + 1] += val[i];
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) 
    b[i][j] += b[i-1][j] + b[i][j-1] - b[i-1][j-1],
    a[i][j] += b[i][j], 
    c[i][j] = max(a[i][j], max(c[i-1][j], c[i][j-1]));
  for (int i = n; i; --i) for (int j = m; j; --j)
    d[i][j] = max(a[i][j], max(d[i+1][j], d[i][j+1]));
    
  int res = c[n][m];
  for (int i = 0; i < q; ++i) 
    res = min(res, max({c[n][m] - val[i], c[r1[i] - 1][m], c[n][c1[i] - 1], d[r2[i] + 1][1], d[1][c2[i] + 1]}));
  cout << res;
	return 0;
}


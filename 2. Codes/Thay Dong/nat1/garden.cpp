#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int N = 2005;
int a[N], b[N], n, m, L, W;

ll sqr(ll x) { return x * x; }
ld cost(int i, int j) { return sqrt(sqr(a[i] - b[j]) + sqr(W)); }

int bit[N][N];

int get(int x, int y) {
  int res = 1e9;
  for (int i = x + 1; i; i -= i & -i)
    for (int j = y + 1; j; j -= j & -j)
      res = min(res, bit[i][j]);
  return res;
}

void update(int x, int y, int val) {
  for (int i = x + 1; i <= n; i += i & -i)
    for (int j = y + 1; j <= m; j += j & -j)
      bit[i][j] = min(bit[i][j], val);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> L >> W;
    cin >> n;
    for (int i = 0; i < n; ++i)
      cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; ++i)
      cin >> b[i];
    vector<tuple<double, int, int>> c, d; 
    c.reserve(n * m); d.reserve(n * m);
    for (int i1 = 0; i1 < n; ++i1) 
      for (int i2 = 0; i2 < m; ++i2) 
        c.emplace_back(cost(i1, i2) - a[i1] - b[i2], i1, i2),
        d.emplace_back(L - a[i1] - b[i2] - cost(i1, i2), i1, i2);
    
    sort(c.begin(), c.end());
    sort(d.begin(), d.end());
    
    memset(bit, 0x3f, sizeof(bit));

    int res = 0; ld val1, val2;
    for (int i = 0, j = 0, i1, i2, j1, j2; i < d.size(); ++i) {
      tie(val1, i1, i2) = d[i];
      while (j < c.size()) {
        tie(val2, j1, j2) = c[j];
        if (val2 > val1) break;
        update(j1, j2, j1 + j2); j++;
      }
      res = max(res, i1 + i2 - get(i1, i2) + 2);
    }
    cout << res << '\n';
  }
	return 0;
}


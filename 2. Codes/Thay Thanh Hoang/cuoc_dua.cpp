#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1005;
string s[N];

bitset<N> f[N][N], g[N][N];

vector<tuple<int, int, int, int>> queries[N];
int ans[N * N];
int n, m, q;

void solve(int l, int r) {
  if (l > r) return;
  int mid = l+r >> 1;
  // tu (i, j) co den dc (mid, y) hay ko
  // f[i][j][y] = f[i][j + 1][y] | f[i + 1][j][y] 
  // f[i][j] = f[i][j + 1] | f[i + 1][j]
  // tu (mid, y) co den dc(i, j) hay ko
  // g[i][j][y] = g[i][j - 1][y] | g[i - 1][j][y]
  // g[i][j] = g[i][j - 1] | g[i - 1][j]
  
  for (int i = 1; i <= m; ++i)
    f[mid][i][i] = g[mid][i][i] = 1;
  for (int i = mid; i >= l; --i)
    for (int j = m; j; --j) if (s[i][j] == '.')
      f[i][j] |= f[i + 1][j] | f[i][j + 1];
    else f[i][j].reset();
  for (int i = mid; i <= r; ++i)
    for (int j = 1; j <= m; ++j) if (s[i][j] == '.') 
      g[i][j] |= g[i - 1][j] | g[i][j - 1];
    else f[i][j].reset();
  for (int r1 = l; r1 <= mid; ++r1) {
    while (!queries[r1].empty()) {
      auto q = queries[r1].back();
      int c1, r2, c2, id; tie(r2, c1, c2, id) = q; 
      if (r2 >= mid) ans[id] = (f[r1][c1] & g[r2][c2]).any(), queries[r1].pop_back();
      else break;
    }
  }
  for (int i = l; i <= r; ++i)
    for (int j = 1; j <= m; ++j)
      f[i][j].reset(), g[i][j].reset();
  
  solve(l, mid - 1);
  solve(mid + 1, r);
  
    
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i)
    cin >> s[i], s[i] = ' ' + s[i];
  for (int i = 0, r1, c1, r2, c2; i < q; ++i) {
    cin >> r1 >> c1 >> r2 >> c2;
    queries[r1].emplace_back(r2, c1, c2, i);
  }
  for (int r1 = 1; r1 <= n; ++r1)
    sort(queries[r1].begin(), queries[r1].end());
  solve(1, n);
  
  for (int i = 0; i < q; ++i)
    cout << (ans[i] ? "YES\n" : "NO\n");
	return 0;
}


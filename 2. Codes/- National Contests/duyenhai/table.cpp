#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 500 + 5;
struct Q {
  int x, y, u, v, w;
  Q(int x, int y, int u, int v, int w): x(x), y(y), u(u), v(v), w(w) {}
};
ll a[N][N], b[N][N];
int n, m, q;
ll g(Q qu, int x, int y, int u, int v) {
    int x5 = max(qu.x, x);
    int y5 = max(qu.y, y);
    int x6 = min(qu.u, u);
    int y6 = min(qu.v, v);
    if (x5 > x6 || y5 > y6) return 0;
    return 1LL * (x6 - x5 + 1) * (y6 - y5 + 1); 
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      cin >> a[i][j],
      a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
  vector<Q> que; que.reserve(N);
  int K = 2;
  for (int i = 0, t, x, y, u, v, w; i < q; ++i) {
    cin >> t >> x >> y >> u >> v;
    if (t == 1) {
      cin >> w;
      que.emplace_back(x, y, u, v, w);
      if (que.size() == K) {
        memset(b, 0, sizeof(b));
        for (auto& qu : que) 
          b[qu.x][qu.y] += qu.w,
          b[qu.x][qu.v+1] -= qu.w,
          b[qu.u+1][qu.y] -= qu.w,
          b[qu.u+1][qu.v+1] += qu.w;
        for (int i = 1; i <= n; ++i)
          for (int j = 1; j <= m; ++j)
            b[i][j] += b[i-1][j] + b[i][j-1] - b[i-1][j-1];
        for (int i = 1; i <= n; ++i)
          for (int j = 1; j <= m; ++j)
            b[i][j] += b[i-1][j] + b[i][j-1] - b[i-1][j-1],
            a[i][j] += b[i][j];
        que.clear();
      }
    } else {
      ll res = a[u][v] - a[x-1][v] - a[u][y-1] + a[x-1][y-1];
      for (auto& qu : que)
        res += g(qu, x, y, u, v) * qu.w;
      cout << res << '\n';
    }
  }
	return 0;
}


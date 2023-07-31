#include<bits/stdc++.h>
using namespace std;
using ll = long long;

template<class X, class Y> 
bool cmin(X& a, Y b) {
  return b < a ? a = b, 1 : 0;
}

const int N = 200 + 5;
const int inf = 1e9;
struct Edge {
  int u, v, w;
  Edge() = default;
  Edge(int u, int v, int w): u(u), v(v), w(w) {}
};
int dis[N][N], src[N][N], res[N * N];
int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));
    vector<Edge> edges;
    for (int i = 0, u, v, w; i < m; ++i)
      cin >> u >> v >> w,
      dis[u][v] = dis[v][u] = w,
      src[u][v] = src[v][u] = i,
      edges.emplace_back(u, v, w);
    for (int u = 0; u < n; ++u)
      dis[u][u] = 0;
    for (int k = 0; k < n; ++k) for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v)
      if (dis[u][k] + dis[k][v] < dis[u][v]) 
        dis[u][v] = dis[u][k] + dis[k][v],
        src[u][v] = src[u][k], src[v][u] = src[v][k];
    fill(begin(res), end(res), inf);
    for (int s = 0; s < n; ++s) for (int i = 0; i < m; ++i) {
      int u = edges[i].u, v = edges[i].v, w = edges[i].w;
      if (u == s) {
        if (src[u][v] != i) cmin(res[i], dis[u][v] + w);
      } else if (v == s) {
        if (src[v][u] != i) cmin(res[i], dis[v][u] + w);
      } else if (src[s][u] != src[s][v])
        cmin(res[src[s][u]], dis[s][u] + dis[s][v] + w),
        cmin(res[src[s][v]], dis[s][v] + dis[s][u] + w);
    }
    cout << "Case " << tc << ":\n";
    for (int i = 0; i < m; ++i)
      if (res[i] == inf) cout << "impossible\n";
      else cout << res[i] - edges[i].w + 1 << '\n';
  }
	return 0;
}


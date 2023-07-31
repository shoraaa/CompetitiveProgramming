#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
const int N = 1e5 + 5, M = 1e9 + 7;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
void sub(int& x, int y) {
  x -= y; if (x < 0) x += M;
}
int mul(ll x, ll y) {
  return x * y % M;
}
struct Edge {
  int u, v, w;
  Edge(int u, int v, int w): u(u), v(v), w(w) {}
};
struct AdjacentEdge {
  int v, w;
  AdjacentEdge(int v, int w): v(v), w(w) {}
};
struct State {
  int u; ll d;
  State(int u, ll d): u(u), d(d) {}
  bool operator < (const State& s) const {
    return d > s.d;
  }
};
vector<AdjacentEdge> adj[N];
vector<Edge> edges;
ll dis[2][N]; int cnt[2][N];
int n, m, s[2];
Edge rev(Edge e) {
  return Edge(e.v, e.u, e.w);
}
int on_path(int t, Edge e) {
  return dis[t][e.u] + e.w == dis[t][e.v] && dis[t][e.v] + dis[t^1][e.v] == dis[t][s[t^1]]; 
}
signed main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> s[0] >> s[1], s[0]--, s[1]--;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    adj[u].emplace_back(v, w),
    adj[v].emplace_back(u, w),
    edges.emplace_back(u, v, w), edges.emplace_back(v, u, w);
  priority_queue<State> q;
  for (int t = 0; t < 2; ++t) {
    memset(dis[t], 0x3f, sizeof(dis[t]));
    q.emplace(s[t], 0); dis[t][s[t]] = 0; cnt[t][s[t]] = 1;
    while (!q.empty()) {
      auto s = q.top(); q.pop();
      if (s.d != dis[t][s.u]) continue;
      for (auto& c : adj[s.u]) if (s.d + c.w < dis[t][c.v])
        dis[t][c.v] = s.d + c.w, cnt[t][c.v] = cnt[t][s.u], q.emplace(c.v, dis[t][c.v]);
      else if (s.d + c.w == dis[t][c.v])
        add(cnt[t][c.v], cnt[t][s.u]);
    }
  }
  int res = mul(cnt[0][s[1]], cnt[1][s[0]]);
  for (int v = 0; v < n; ++v) if (dis[0][v] == dis[1][v])
    sub(res, mul(mul(cnt[0][v], cnt[1][v]), mul(cnt[1][v], cnt[0][v])));
  for (auto& c : edges) 
    if (on_path(0, c) && on_path(1, rev(c)) && abs(dis[0][c.u] - dis[1][c.v]) < c.w)
      sub(res, mul(mul(cnt[0][c.u], cnt[1][c.v]), mul(cnt[1][c.v], cnt[0][c.u])));
  cout << res;
	return 0;
}


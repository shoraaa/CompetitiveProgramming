#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 1e5 + 5;
struct Adjacent {
  int v, w;
  Adjacent(int v, int w): v(v), w(w) {}
};
struct Edge {
  int u, v, w;
  Edge(int u, int v, int w): u(u), v(v), w(w) {}
};
struct State {
  int u; ll d;
  State(int u, ll d): u(u), d(d) {}
  bool operator < (const State& s) const {
    return d > s.d;
  }
};
vector<Adjacent> adj[2][N];
vector<Edge> edges;
ll dis[2][N]; ull cnt[2][N];
int n, m;
int on_path(int u, int v, int w) {
  return dis[0][u] + dis[1][v] + w == dis[0][1];
}
void solve(int tp, int s) {
  priority_queue<State> q;
  memset(dis[tp], 0x3f, sizeof(dis[tp]));
  q.emplace(s, 0); cnt[tp][s] = 1, dis[tp][s] = 0;
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    if (s.d != dis[tp][s.u]) continue;
    for (auto& c : adj[tp][s.u]) if (s.d + c.w < dis[tp][c.v])
      dis[tp][c.v] = s.d + c.w, cnt[tp][c.v] = cnt[tp][s.u],
      q.emplace(c.v, dis[tp][c.v]);
    else if (s.d + c.w == dis[tp][c.v])
      cnt[tp][c.v] += cnt[tp][s.u];
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; vector<Edge> edges;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    adj[0][u].emplace_back(v, w),
    adj[1][v].emplace_back(u, w),
    edges.emplace_back(u, v, w);
  solve(0, 0), solve(1, 1);
  for (auto& edge : edges) {
    int u = edge.u, v = edge.v, w = edge.w;
    if (on_path(u, v, w)) {
      if (cnt[0][u] * cnt[1][v] == cnt[0][1])
        cout << "SAD\n";
      else
        cout << "SOSO\n";
    } else {
      if (dis[0][v] + dis[1][u] + w < dis[0][1])
        cout << "HAPPY\n";
      else 
        cout << "SOSO\n";
    }
  }
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct Adjacent {
  int v, i;
  Adjacent(int v, int i): v(v), i(i) {}
};
struct State {
  int u; ll d;
  State(int u, ll d): u(u), d(d) {}
  bool operator < (const State& s) const {
    return d > s.d;
  }
};
const int N = 5e4 + 5;
vector<Adjacent> adj[N], rev[N];
int w[2][N], cost[N]; ll dis[N];
int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	if (fopen("gps.in", "r"))
	  freopen("gps.in", "r", stdin),
	  freopen("gps.out", "w", stdout);
  cin >> n >> m;
  for (int i = 0, u, v, p, q; i < m; ++i)
    cin >> u >> v >> p >> q, u--, v--,
    w[0][i] = p, w[1][i] = q,
    adj[u].emplace_back(v, i),
    rev[v].emplace_back(u, i);
  priority_queue<State> q;
  for (int tw = 0; tw < 2; ++tw) {
    memset(dis, 0x3f, sizeof(dis));
    int s = n-1, t = 0;
    q.emplace(s, 0); dis[s] = 0;
    while (!q.empty()) {
      auto s = q.top(); q.pop();
      if (s.d != dis[s.u]) continue;
      for (auto& c : rev[s.u]) if (s.d + w[tw][c.i] < dis[c.v])
        dis[c.v] = s.d + w[tw][c.i],
        q.emplace(c.v, dis[c.v]);
    }
    for (int u = 0; u < n; ++u) for (auto& c : adj[u])
      if (dis[c.v] + w[tw][c.i] != dis[u]) cost[c.i]++;
  }
  memset(dis, 0x3f, sizeof(dis));
  q.emplace(0, 0); dis[0] = 0;
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    if (s.d != dis[s.u]) continue;
    for (auto& c : adj[s.u]) if (s.d + cost[c.i] < dis[c.v])
      dis[c.v] = s.d + cost[c.i],
      q.emplace(c.v, dis[c.v]);
  }
  cout << dis[n-1];
	return 0;
}


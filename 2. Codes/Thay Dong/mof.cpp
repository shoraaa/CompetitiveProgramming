#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e2 + 5, M = 500 * 100 + 5;
struct Adjacent {
  int v, c, t;
  Adjacent(int v, int c, int t): v(v), c(c), t(t) {}
};
struct State {
  int u, c;
  State(int u, int c): u(u), c(c) {}
};
vector<Adjacent> adj[N];
int dis[N][M];
vector<State> q[M];
int n, m, s, t;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> s >> t; s--, t--; int max_c = 0;
  for (int i = 0, u, v, c, t; i < m; ++i)
    cin >> u >> v >> c >> t, u--, v--, max_c = max(max_c, c),
    adj[u].emplace_back(v, c, t),
    adj[v].emplace_back(u, c, t);
  memset(dis, 0x3f, sizeof(dis));
  q[0].emplace_back(s, 0);
  dis[s][0] = 0; int lim = m*max_c;
  for (int d = 0; d < lim; ++d) {
    while (!q[d].empty()) {
      auto s = q[d].back(); q[d].pop_back();
      if (d != dis[s.u][s.c]) continue;
      for (auto& c : adj[s.u]) if (d + c.t < dis[c.v][s.c + c.c] && s.c + s.c < lim)
        dis[c.v][s.c + c.c] = d + c.t,
        q[d + c.t].emplace_back(c.v, s.c + c.c);
    }
  }
  ll res = 0; 
  for (int c = 0, cur = 1e9; c < lim; ++c) if (dis[t][c] < cur) 
    cur = dis[t][c], res++;
  cout << res;
	return 0;
}


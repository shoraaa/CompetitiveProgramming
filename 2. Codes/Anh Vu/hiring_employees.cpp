#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1000 + 5, inf = INT_MAX;
const ll llinf = 1e18;
int n, m, s, t;
struct MaxFlowMinCost {
  struct FlowEdge {
    int u, v, c, w;
    FlowEdge(int u, int v, int c, int w): u(u), v(v), c(c), w(w) {}
  };
  vector<FlowEdge> e;
  vector<int> adj[N];
  void add(int u, int v, int c, int w) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, c, w);
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, 0, -w);
  }
  int par[N], inq[N];
  ll dis[N];
  ll cost = 0;
  void add_flow() {
    int u = t, f = inf; stack<int> st;
    while (u != s) 
      st.emplace(par[u]),
      f = min(f, e[par[u]].c),
      u = e[par[u]].u;
    while (!st.empty()) 
      u = st.top(),
      cost += ll(f) * e[u].w,
      e[u].c -= f, 
      e[u ^ 1].c += f,
      st.pop();
  }
  int bfs() {
    queue<int> q;
    fill(begin(dis), end(dis), llinf);
    q.emplace(s), dis[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop(); inq[u] = 0;
      for (int i : adj[u]) if (dis[u] + e[i].w < dis[e[i].v] && e[i].c > 0) {
        par[e[i].v] = i,
        dis[e[i].v] = dis[u] + e[i].w;
        if (!inq[e[i].v])
          q.emplace(e[i].v), inq[e[i].v] = 1;
      }
    }
    if (dis[t] != llinf)
      return add_flow(), 1;
    return 0;
  }
  ll calculate() {
    while (bfs());
    return cost;
  }
} min_cost;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; s = 0, t = n+2;
  min_cost.add(s, 1, inf, 0);
  min_cost.add(n+1, t, inf, 0);
  for (int i = 1, x; i <= n; ++i)
    cin >> x,
    min_cost.add(i, i+1, inf - x, 0);
  for (int i = 0, l, r, c; i < m; ++i) 
    cin >> l >> r >> c,
    min_cost.add(l, r+1, inf, c);
  cout << min_cost.calculate();
	return 0;
}


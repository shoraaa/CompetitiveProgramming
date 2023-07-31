#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2000 + 5, oo = INT_MAX;
int n, s, t;
vector<int> ans;
int vis[N];
struct max_flow {
  struct edge {
    int u, v, rem, val;
    edge(int u, int v, int rem): u(u), v(v), rem(rem), val(rem) {}
  };
  vector<edge> edges;
  vector<int> G[N];
  int par[N];
  void add_edge(int u, int v, int c) {
    G[u].emplace_back(edges.size());
    edges.emplace_back(u, v, c);
    
    G[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0);
  }
  int bfs() {
    queue<pair<int, int>> q;
    q.emplace(s, oo);
    memset(par, -1, sizeof(par));
    par[s] = -1;
    while (!q.empty()) {
      int u = q.front().first, f = q.front().second; q.pop();
      if (u == t) 
        return f;
      for (int id : G[u]) if (!~par[edges[id].v] && edges[id].rem)
        par[edges[id].v] = id, q.emplace(edges[id].v, min(f, edges[id].rem));
    } 
    return 0;
  }
  int calc() {
    int flow, min_cut = 0;
    while (flow = bfs()) {
      int u = t; min_cut += flow;
      while (u != s) {
        int id = par[u];
        edges[id].rem -= flow;
        edges[id ^ 1].rem += flow;
        u = edges[id].u;
      }
    }
    queue<int> q; 
    q.emplace(s);
    vis[s] = 1;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int id : G[u]) if (!vis[edges[id].v] && edges[id].rem)
        vis[edges[id].v] = 1, q.emplace(edges[id].v);
    } 
    for (int u = 0; u < n; ++u) 
      if (vis[u] && !vis[u + n]) 
        ans.emplace_back(u);
    return ans.size();
  }
} mf;
int m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> s >> t, s--, t--; t += n;
  for (int i = 0, c; i < n; ++i)
    cin >> c, mf.add_edge(i, i + n, c);
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--,
    mf.add_edge(u + n, v, oo),
    mf.add_edge(v + n, u, oo);
  cout << mf.calc() << '\n';
  for (int u : ans)
    cout << u + 1 << ' ';
	return 0;
}


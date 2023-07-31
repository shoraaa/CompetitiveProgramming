#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2000 + 5, oo = 1e9;
int s, t;
struct max_flow {
  struct edge {
    int u, v, rem;
    edge(int u, int v, int rem): u(u), v(v), rem(rem) {}
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
    return min_cut;
  }
} mf;
int L, W, n;
int x[N], y[N];
ll sqr(ll x) {
  return x * x;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> L >> W >> n; s = 0, t = 2*n+1;
  for (int i = 1; i <= n; ++i)
    cin >> x[i] >> y[i],
    mf.add_edge(i, i + n, 1);
  for (int i = 1; i <= n; ++i) {
    if (y[i] <= 100) 
      mf.add_edge(s, i, oo);
    if (y[i] >= W - 100) 
      mf.add_edge(i + n, t, oo);
    for (int j = i + 1; j <= n; ++j) 
      if (sqr(x[i] - x[j]) + sqr(y[i] - y[j]) <= 40000) 
        mf.add_edge(i + n, j, oo),
        mf.add_edge(j + n, i, oo);
  }
  cout << mf.calc();
	return 0;
}


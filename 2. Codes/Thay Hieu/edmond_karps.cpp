#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1000 + 5, oo = 1e9;
int n, s, t;
struct max_flow {
  struct edge {
    int  u, v, rem;
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
    int flow, res = 0;
    while (flow = bfs()) {
      res += flow;
      int u = t;
      while (u != s) {
        int id = par[u];
        edges[id].rem -= flow;
        edges[id ^ 1].rem += flow;
        u = edges[id].u;
      }
    }
    return res;
  }
} mf;
int m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> s >> t, s--, t--;
  for (int i = 0, u, v, c; i < m; ++i)
    cin >> u >> v >> c, u--, v--, 
    mf.add_edge(u, v, c);
  cout << mf.calc();
	return 0;
}


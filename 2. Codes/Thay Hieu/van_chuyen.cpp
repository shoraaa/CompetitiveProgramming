#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5, oo = 2e9;
int n, s, t;
ll dis[N];
int notin[N];
struct S {
  int u; ll d;
  S(int u,  ll d): u(u), d(d) {}
  bool operator < (const S& s) const {
    return d > s.d;
  }
};
struct max_flow {
  struct edge {
    int u, v, cap;
    edge(int u, int v, int c): u(u), v(v), cap(c) {}
  };
  vector<edge> edges;
  vector<int> G[N];
  int par[N];
  stack<pair<int, int>> stk;
  void rollback() {
    while (!stk.empty()) {
      int u = stk.top().first, v = stk.top().second; stk.pop();
      G[u].pop_back(), G[v].pop_back();
      edges.pop_back(), edges.pop_back();
    }
    for (int id = 0; id < edges.size(); ++id)
      edges[id].cap = id % 2 == 0;
  }
  void add_edge(int u, int v, int t = 0) {
    G[u].emplace_back(edges.size());
    edges.emplace_back(u, v, 1);
    
    G[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0);
    
    if (t) stk.emplace(u, v);
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
      for (int id : G[u]) if (!~par[edges[id].v] && edges[id].cap)
        par[edges[id].v] = id, q.emplace(edges[id].v, min(f, edges[id].cap));
    } 
    return 0;
  }
  int calc() {
    int flow, min_cut = 0;
    while (flow = bfs()) {
      int u = t; min_cut += flow;
      while (u != s) {
        int id = par[u];
        edges[id].cap -= flow;
        edges[id ^ 1].cap += flow;
        u = edges[id].u;
      }
    }
    return min_cut;
  }
} mf;
struct C {
  int v, w;
  C(int v, int w): v(v), w(w) {}
};
vector<C> G[N];
int m, k;
int a[N];
signed main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m >> k; s = 0, t = 1;
	mf.edges.reserve(m * 4);
	for (int i = 0, u, v, w; i < m; ++i)
	  cin >> u >> v >> w,
	  G[u].emplace_back(v, w),
	  G[v].emplace_back(u, w);
	priority_queue<S> q; q.emplace(t, 0);
	memset(dis, 0x3f, sizeof(dis)); dis[t] = 0;
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    if (s.d != dis[s.u]) continue;
    for (C& c : G[s.u]) if (s.d + c.w < dis[c.v])
      dis[c.v] = s.d + c.w,
      q.emplace(c.v, dis[c.v]);
  }
  for (int u = 1; u <= n; ++u)
    for (C& c : G[u]) if (dis[u] + c.w == dis[c.v])
      mf.add_edge(c.v, u);
	int res = 0;
	for (int i = 0, u; i < k; ++i)
	  cin >> a[i];
	sort(a, a + k, [&](int u, int v) {
	  return dis[u] < dis[v];
	});
	for (int i = 0; i < k;) {
	  int j = i; mf.rollback();
	  while (j < k && dis[a[j]] == dis[a[i]])
	    mf.add_edge(s, a[j], 1), j++;
	  res += mf.calc(); i = j;
	}
	cout << res;
	return 0;
}


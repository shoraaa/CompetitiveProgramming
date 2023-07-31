#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 5;
struct Edge {
  int u, v, w = 0, in = 0;
  Edge(int u, int v): u(u), v(v) {}
};
struct Adjacent {
  int v, i;
  Adjacent(int v, int i): v(v), i(i) {}
};
vector<Edge> edges;
vector<Adjacent> adj[N];
int dep[N], par[N], lin[N], idx[N], low[N];
void build(int u = 0, int p = -1) {
  for (auto& c : adj[u]) if (c.v != p) 
    dep[c.v] = dep[u] + 1, 
    par[c.v] = u, idx[c.v] = c.i, low[c.i] = c.v,
    build(c.v, u);
}
int find(int u) {
  if (lin[u] == u) return u;
  return lin[u] = find(lin[u]);
}
void paint(int u) {
  lin[u] = par[u];
}
int n, m;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--,
    edges.emplace_back(u, v);
  for (int i = 0, id; i < n-1; ++i) {
    cin >> id, id--, edges[id].in = 1;
    int u = edges[id].u, v = edges[id].v;
    adj[u].emplace_back(v, id);
    adj[v].emplace_back(u, id);
  }
  build();
  for (int u = 0; u < n; ++u)
    lin[u] = u;
  for (int i = 0, w = 0; i < m; ++i) {
    if (!edges[i].in) {
      vector<int> path; 
      int u = find(edges[i].u), v = find(edges[i].v);
      while (u != v) {
        if (dep[u] < dep[v]) swap(u, v);
        path.emplace_back(u); paint(u);
        u = find(u);
      }
      sort(path.begin(), path.end(), [](int u, int v) {
        return idx[u] < idx[v];
      });
      for (int u : path)
        edges[idx[u]].w = ++w;
      edges[i].w = ++w;
    } else if (!edges[i].w) {
      edges[i].w = ++w,
      paint(low[i]);
    }
    cout << edges[i].w << ' ';
  }
	return 0;
}


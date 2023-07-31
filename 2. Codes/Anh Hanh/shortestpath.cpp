#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll llinf = 1e18;
void file() {
	const string FILE_NAME = "shortestpath";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 5e5 + 5;
struct C {
  int v, w;
  C(int v, int w): v(v), w(w) {}
};
struct S {
  int u; ll d;
  S(int u, ll d): u(u), d(d) {}
  bool operator < (const S& s) const {
    return d > s.d;
  }
};
vector<C> adj[N], dir[N], dag[N];
ll dis[N];
int par[N], vis[N]; 
vector<int> cont[N];
void dfs(int u, int p) {
  par[u] = p, cont[p].emplace_back(u);
  vis[u] = 1;
  for (C& c : adj[u]) if (!vis[c.v])
    dfs(c.v, p);
  for (C& c : dir[u]) {
    if (!vis[c.v])
      dfs(c.v, c.v);
    dag[p].emplace_back(par[c.v], c.w);
  }
}
vector<int> order;
void topo(int p) {
  vis[p] = 1;
  for (C& c : dag[p])
    if (!vis[c.v]) topo(c.v);
  order.emplace_back(p);
}
int n, m, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
  cin >> n >> m >> k;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    adj[u].emplace_back(v, w),
    adj[v].emplace_back(u, w);
  for (int i = 0, u, v, w; i < k; ++i)
    cin >> u >> v >> w, u--, v--,
    dir[u].emplace_back(v, w);

  memset(par, -1, sizeof(par));
  dfs(0, 0);
  
  memset(vis, 0, sizeof(vis));
  for (int u = 0; u < n; ++u)
    if (~par[u] && !vis[par[u]]) topo(par[u]);
  reverse(order.begin(), order.end());
  
  fill(begin(dis), end(dis), llinf);
  dis[0] = 0; priority_queue<S> q;
  for (int p : order) {
    for (int u : cont[p])
      if (dis[u] != llinf) q.emplace(u, dis[u]);
    while (!q.empty()) {
      auto s = q.top(); q.pop();
      if (s.d != dis[s.u]) continue;
      for (C& c : adj[s.u]) if (s.d + c.w < dis[c.v])
        dis[c.v] = s.d + c.w,
        q.emplace(c.v, dis[c.v]);
    }
    for (int u : cont[p])
      for (C& c : dir[u]) 
        dis[c.v] = min(dis[c.v], dis[u] + c.w);
  }
  
  for (int u = 0; u < n; ++u)
    cout << (dis[u] == llinf ? -1 : dis[u]) << ' ';
  return 0;
}


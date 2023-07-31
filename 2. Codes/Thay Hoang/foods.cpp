#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
const ll inf = 1e18;
void file() {
  const string FILE_NAME = "foods";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
int n, m, s, t;
struct dinic {
  struct edge {
    int u, v; ll cap;
    edge(int u, int v, int c): u(u), v(v), cap(c) {}
  };
  vector<edge> edges;
  vector<int> adj[N];
  int cur[N], level[N];
  ll lwb;
  void add(int u, int v, int c) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(u, v, c);
    adj[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0);
  }
  int bfs() {
    queue<int> q;
    q.emplace(s);
    memset(level, -1, sizeof(level));
    level[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int id : adj[u]) if (!~level[edges[id].v] && edges[id].cap >= lwb)
        level[edges[id].v] = level[u] + 1, 
        q.emplace(edges[id].v);
    }
    return ~level[t];
  }
  ll dfs(int u, ll pushed) {
    if (u == t)
      return pushed;
    int sum = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int id = adj[u][cur[u]], v = edges[id].v, push; ll cap = edges[id].cap;
      if (cap < lwb || level[u] + 1 != level[v]) continue;
      if (push = dfs(v, min(pushed, cap))) 
        edges[id].cap -= push, 
        edges[id ^ 1].cap += push, 
        pushed -= push, sum += push;
      if (pushed == 0)
        return sum; 
    }
    return sum;
  }
  int vis[N];
  vector<int> lef, rig;
  void build(int u, int inRight = 0) {
    if (inRight) rig.emplace_back(u - n);
    vis[u] = 1;
    for (int i : adj[u]) if (!vis[edges[i].v] && edges[i ^ inRight].cap != inRight) 
      build(edges[i].v, !inRight);
    
  }
  void max_flow(ll b) {
    ll res = 0; lwb = b;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      res += dfs(s, inf);
    }
    vis[s] = vis[t] = 1;
    for (int u = 1; u <= n; ++u) {
      int flow = 0;
      for (int i : adj[u]) 
        flow += edges[i].v && !edges[i].cap;
      if (flow == 0)
        build(u);
    }
    for (int u = 1; u <= n; ++u)
      if (!vis[u]) lef.emplace_back(u);
    memset(vis, 0, sizeof(vis));
    for (int u : lef) vis[u] = 1;
    for (int u : rig) vis[u+n] = 1;
    vector<int> l, r;
    for (int u = 1; u <= n; ++u)
      if (!vis[u]) l.emplace_back(u);
    for (int u = 1; u <= m; ++u)
      if (!vis[u+n]) r.emplace_back(u);
    cout << l.size() << ' ' << r.size() << '\n';
    for (int u : l) cout << u << ' ';
    cout << '\n';
    for (int u : r) cout << u << ' ';
  }

  void reshuffle() {
    for (int u = 0; u < n; ++u)
      shuffle(adj[u].begin(), adj[u].end(), rng);
  }
} din;
int k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
  cin >> n >> m >> k; s = 0, t = n+m+1;
  int u, v; din.edges.reserve(m * 6);
  while (cin >> u >> v) 
    din.add(u, v + n, 1);
  for (int u = 1; u <= n; ++u)
    din.add(s, u, 1);
  for (int v = 1; v <= m; ++v)
    din.add(v + n, t, 1);
  //din.reshuffle();
  din.max_flow(1);
	return 0;
}


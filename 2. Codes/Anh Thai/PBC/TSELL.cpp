#include<bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int N = 2e5 + 5, K = 14, inf = 2e9;
 
int n, k, s, t, id = 0;
struct MaxFlow {
  struct FlowEdge {
    int u, v, c;
    FlowEdge(int u, int v, int c): u(u), v(v), c(c) {}
  };
  vector<FlowEdge> edges;
  vector<int> adj[N];
  void add(int u, int v, int c) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(u, v, c);
    
    adj[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0);
  }
  
  int dis[N];
  queue<int> q;
  int bfs() {
    memset(dis, -1, sizeof(dis));
    q.emplace(s); dis[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int e : adj[u]) {
        int v = edges[e].v, c = edges[e].c;
        if (c > 0 && !~dis[v])
          dis[v] = dis[u] + 1,
          q.emplace(v); 
      }
    }
    return ~dis[t];
  }
  
  int cur[N];
  ll dfs(int u, ll flow) {
    if (u == t) 
      return flow;
    ll sum = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int e = adj[u][cur[u]], v = edges[e].v, c = edges[e].c;
      if (dis[v] != dis[u] + 1 || c <= 0) continue;
      if (int pushed = dfs(v, min(flow, ll(c))))
        flow -= pushed, sum += pushed,
        edges[e].c -= pushed,
        edges[e^1].c += pushed;
      if (flow == 0)  
        return sum;
    }
    return sum;
  }
  
  ll get() {
    ll res = 0;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      res += dfs(s, inf);
    }
    return res;
  }
  
} flow;
 
vector<int> adj[N];

int par[N][K], idx[N][K], dep[N], a[N], b[N];

int lca(int u, int v) {
  if (dep[u] <= dep[v]) swap(u, v);
  for (int i = K-1; ~i; --i) if (dep[par[u][i]] >= dep[v]) u = par[u][i];
  if (u == v) return u;
  for (int i = K-1; ~i; --i) if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
  return par[u][0];
}

void dfs(int u = 1, int p = 0) {
  dep[u] = dep[p] + 1;
  par[u][0] = p; idx[u][0] = id++;
  flow.add(idx[u][0], b[u], inf);
  for (int i = 1; i < K; ++i)
    par[u][i] = par[par[u][i-1]][i-1],
    idx[u][i] = id++, 
    flow.add(idx[u][i], idx[u][i-1], inf),
    flow.add(idx[u][i], idx[par[u][i-1]][i-1], inf);
  for (int v : adj[u]) if (v != p)
    dfs(v, u);
}
 
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k; s = id++, t = id++;
  for (int i = 1, w; i <= n; ++i) 
    cin >> w, b[i] = id++, flow.add(b[i], t, w);
  for (int i = 0, u, v, c; i < n-1; ++i) 
    cin >> u >> v,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  for (int i = 0; i < K; ++i) idx[0][i] = id++;
  dfs(); 
  for (int i = 0, u, v, l, w; i < k; ++i) {
    cin >> u >> v >> w;
    a[i] = id++, l = lca(u, v); flow.add(s, a[i], w);
    for (int j = K-1; ~j; --j) if (dep[par[u][j]] >= dep[l])
      flow.add(a[i], idx[u][j], inf), u = par[u][j];
    for (int j = K-1; ~j; --j) if (dep[par[v][j]] >= dep[l])
      flow.add(a[i], idx[v][j], inf), v = par[v][j];
    flow.add(a[i], idx[l][0], inf);
  }
  cout << flow.get();
	return 0;
}
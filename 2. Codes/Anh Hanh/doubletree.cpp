#include<bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int N = 235 + 5, inf = 2e9;
 
int n, m, s, t;
struct MaxFlow {
  struct Edge {
    int u, v, c;
    Edge(int u, int v, int c): u(u), v(v), c(c) {}
  };
  vector<Edge> edges;
  vector<int> adj[N];
  void add(int u, int v, int c) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(u, v, c);
    
    adj[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0);
  }
  void reset() {
    for (int i = 0; i <= n + 1; ++i) 
      adj[i].clear();
    edges.clear();
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

vector<int> adj[2][N];
int a[N];

void dfs(int id, int u, int p = -1) {
  if (p != -1) flow.add(u, p, inf);
  for (int v : adj[id][u]) 
    if (v != p) dfs(id, v, u);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("doubletree.inp", "r")) 
    freopen("doubletree.inp", "r", stdin),
    freopen("doubletree.out", "w", stdout);
  int T, sub; cin >> sub >> T;
  while (T--) {
    cin >> n;
    for (int t = 0; t < 2; ++t) {
      for (int i = 0, u, v; i < n - 1; ++i)
        cin >> u >> v, 
        adj[t][u].emplace_back(v),
        adj[t][v].emplace_back(u);
    }
    ll sum = 0;
    for (int i = 1; i <= n; ++i) 
      cin >> a[i], sum += max(a[i], 0);
    s = 0, t = n + 1;
    ll res = 0;
    for (int root = 1; root <= n; ++root) {
      flow.reset();
      for (int i = 1; i <= n; ++i)
        if (a[i] >= 0) flow.add(s, i, a[i]);
        else flow.add(i, t, -a[i]);
      dfs(0, root), dfs(1, root);
      res = max(res, sum - flow.get());
    }
    cout << res << '\n';
    for (int i = 1; i <= n; ++i) 
      adj[0][i].clear(), adj[1][i].clear();
  }
	return 0;
}


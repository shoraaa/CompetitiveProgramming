#include<bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int N = 50000 + 5, inf = 2e9;
 
int n, m, s, t, id, k;
vector<int> adj[N];
int c[N];

struct MaxFlow {
  struct FlowEdge {
    int u, v, c;
    FlowEdge(int u, int v, int c): u(u), v(v), c(c) {}
  };
  vector<FlowEdge> edges;
  vector<int> adj[N];
  void add(int u, int v, int c) {
    //cerr << u << ' ' << v << ' ' << c << '\n';
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
  
};

int idx[105][205];
int check(int lim) {
  MaxFlow flow; id = 0; 
  s = id++, t = id++;
  for (int u = 0; u < n; ++u) {
    for (int i = 0; i <= lim; ++i) idx[u][i] = id++;
    for (int i = 0; i <= lim - 1; ++i) flow.add(idx[u][i], idx[u][i + 1], k);
  }
  for (int u = 0; u < n; ++u) for (int v : adj[u])
    for (int i = 0; i <= lim - 1; ++i) flow.add(idx[u][i], idx[v][i + 1], 1);
  flow.add(s, idx[0][0], k);
  for (int i = 0; i < k; ++i) 
    flow.add(idx[c[i]][lim], t, 1);
  return flow.get();
  
}
 
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; 
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  cin >> k;
  for (int i = 0; i < k; ++i)
    cin >> c[i], c[i]--;

  int lo = 0, hi = n * 2, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid) == k)
      ans = mid, hi = mid - 1;
    else
      lo = mid + 1;
  }
  cout << ans;
	return 0;
}

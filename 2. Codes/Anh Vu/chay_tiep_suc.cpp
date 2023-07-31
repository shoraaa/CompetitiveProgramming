#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define int ll

const int N = 1e5 + 5, inf = 1e16;
vector<pair<int, int>> adj[N];
int special[N];
int n, m, k;

priority_queue<pair<int, int>> q;
int dis[N], src[N];

pair<int, int> dijkstra(int s) {
  memset(dis, 0x3f, sizeof(dis));
  q.emplace(0, s); dis[s] = 0;
  while (!q.empty()) {
    int d, u; tie(d, u) = q.top(); q.pop();
    if (-d != dis[u]) continue;
    if (special[u]) return {dis[u], u};
    for (auto& p : adj[u]) {
      int v, w; tie(v, w) = p;
      if (dis[u] + w < dis[v]) 
        dis[v] = dis[u] + w, q.emplace(-dis[v], v);
    }
  }
  return {inf, 0};
}

tuple<int, int, int> dijkstra0() {
  memset(dis, 0x3f, sizeof(dis));
  for (int v = 0; v < n; ++v) if (special[v])
    dis[v] = 0, src[v] = v, q.emplace(0, v);
  while (!q.empty()) {
    int d, u; tie(d, u) = q.top(); q.pop();
    if (-d != dis[u]) continue;
    for (auto& p : adj[u]) {
      int v, w; tie(v, w) = p;
      if (dis[u] + w < dis[v]) 
        dis[v] = dis[u] + w, src[v] = src[u], q.emplace(-dis[v], v);
    }
  }
  int res = inf, s = -1, t = -1;
  for (int u = 0; u < n; ++u) for (auto& p : adj[u]) {
    int v, w; tie(v, w) = p;
    if (src[u] != src[v] && dis[u] + dis[v] + w < res)
      res = dis[u] + dis[v] + w, s = src[u], t = src[v];
  }
  return make_tuple(res, s, t);
}

signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    adj[u].emplace_back(v, w),
    adj[v].emplace_back(u, w);
    
  for (int i = 0, v; i < k; ++i)
    cin >> v, v--, special[v] = 1;
  
    
  int val1, val2, val3, val4, val5, val6, s, t, t2, tmp1, tmp2;
  tie(val1, s, t) = dijkstra0(); special[s] = special[t] = 0; 
  tie(val2, tmp1, tmp2) = dijkstra0(); 
  
  tie(val3, t2) = dijkstra(s); special[t2] = 0;
  tie(val4, tmp1) = dijkstra(t); special[t2] = 1;
  
  tie(val5, t2) = dijkstra(t); special[t2] = 0;
  tie(val6, tmp1) = dijkstra(s); 
  cout << min({val1 + val2, val3 + val4, val5 + val6});
	return 0;
}


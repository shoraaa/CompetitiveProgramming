#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1005;
const int INF = 1e9;

int n, m, s, t;

struct MaxFlow {
  
  struct Edge {
    int u, v, c;
    Edge(int u, int v, int c): u(u), v(v), c(c) {}
  };
  vector<Edge> ed;
  
  vector<int> adj[N];
  void add(int u, int v, int c) {
    adj[u].emplace_back(ed.size());
    ed.emplace_back(u, v, c);
    
    adj[v].emplace_back(ed.size());
    ed.emplace_back(v, u, 0);
  }
  
  queue<int> q;
  int dis[N], L;
  int bfs() {
    fill(begin(dis), end(dis), INF);
    dis[s] = 0;
    q.emplace(s);
    
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int i : adj[u]) {
        int v = ed[i].v, c = ed[i].c;
        if (c < L || dis[v] <= dis[u] + 1) continue;
        dis[v] = dis[u] + 1;
        q.emplace(v);
      }
    }
    
    return dis[t] != INF;
  }
  
  int cur[N];
  int dfs(int u, int tot) {
    if (u == t) {
      return tot;
    }
    
    int sum = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int i = adj[u][cur[u]];
      if (ed[i].c < L || dis[u] + 1 != dis[ed[i].v]) continue;
      int pushed = dfs(ed[i].v, min(tot - sum, ed[i].c));
      
      ed[i].c -= pushed; ed[i^1].c += pushed;
      sum += pushed;
      
      if (sum == tot) {
        return sum;
      }
      
    }
    
    return sum;
    
  }
  
  int solve() {
    int res = 0;
    for (int i = 19; ~i; --i) {
      L = 1 << i;
      while (bfs()) {
        memset(cur, 0, sizeof(cur));
        res += dfs(s, INF);
      }
    }
    return res;
  }
  
} flow;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> s >> t;
  for (int i = 1, u, v, c; i <= m; ++i) {
    cin >> u >> v >> c;
    flow.add(u, v, c);
  }
  cout << flow.solve();
  
	return 0;
}


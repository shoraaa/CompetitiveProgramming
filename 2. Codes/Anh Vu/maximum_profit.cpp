#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 55000 + 5, inf = 1e9;
int n, m, s, t;
struct MinCut {
  struct FlowEdge {
    int u, v, c;
    FlowEdge(int u, int v, int c): u(u), v(v), c(c) {}
  };
  vector<FlowEdge> e;
  vector<int> adj[N];
  void add(int u, int v, int c) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, c);
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, 0);
  }
  int dis[N], cur[N];
  int bfs() {
    queue<int> q;
    memset(dis, -1, sizeof(dis));
    q.emplace(s);
    dis[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int i : adj[u]) if (!~dis[e[i].v] && e[i].c > 0)
        dis[e[i].v] = dis[u] + 1,
        q.emplace(e[i].v);
    }
    return ~dis[t];
  }
  int dfs(int u, int flow) {
    if (u == t)
      return flow;
    int pushed = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int i = adj[u][cur[u]];
      if (dis[e[i].v] != dis[u] + 1 || e[i].c <= 0) continue;
      if (int push = dfs(e[i].v, min(flow, e[i].c)))
        e[i].c -= push, e[i^1].c += push,
        flow -= push, pushed += push;
      if (flow == 0) break;
    }
    return pushed;
  }
  int calculate() {
    int res = 0, flow;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      res += dfs(s, inf);
    }
    return res;
  }
} min_cut;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; s = 0, t = n+m+1;
  for (int u = 1, c; u <= n; ++u)
    cin >> c, min_cut.add(s, u, c);
  int sum_bonus = 0;
  for (int i = 1, u, v, c; i <= m; ++i) 
    cin >> u >> v >> c, 
    min_cut.add(u, n+i, inf),
    min_cut.add(v, n+i, inf),
    min_cut.add(n+i, t, c),
    sum_bonus += c;
  cout << sum_bonus - min_cut.calculate();
	return 0;
}


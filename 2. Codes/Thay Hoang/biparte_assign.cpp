#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
const ll inf = 1e16;
void file() {
  const string FILE_NAME = "assign";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int n, m, s, t;
 struct edge {
  int u, v, w, cap;
  edge(int u, int v, int w, int c): u(u), v(v), w(w), cap(c) {}
};
struct karp {
  vector<int> adj[N];
  vector<edge> e;
  int inq[N], match[N], cur[N];
  ll dis[N];
  void add(int u, int v, int w) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, w, 1);
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, -w, 0);
  }
  int bfs() {
    queue<int> q;
    memset(inq, 0, sizeof(inq));
    fill(begin(dis), end(dis), inf);
    q.emplace(s), inq[s] = 1, dis[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop(); inq[u] = 0;
      for (int i : adj[u]) if (e[i].cap == 1 && dis[u] + e[i].w < dis[e[i].v]) {
        dis[e[i].v] = dis[u] + e[i].w;
        if (!inq[e[i].v]) 
          inq[e[i].v] = 1, q.emplace(e[i].v);
      }
    }
    return dis[t] != inf;
  }
  ll cost = 0;
  int dfs(int u) {
    if (u == t)
      return 1;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int i = adj[u][cur[u]];
      if (e[i].cap == 0 || dis[u] + e[i].w != dis[e[i].v]) continue;
      if (dfs(e[i].v)) {
        e[i].cap -= 1,
        e[i ^ 1].cap += 1,
        match[u] = i, match[e[i].v] = i ^ 1,
        cost += e[i].w;
        return 1;
      }
    }
    return 0;
  }
  void calc() {
    int res = 0;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      res += dfs(s);
    }
    cout << cost << '\n';
    for (int u = 1; u <= m; ++u) 
      cout << e[match[u + n]].v << ' ';
  }
} kp;
int k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
  cin >> n >> k; m = n, s = 0, t = n+m+1;
  int u, v, w;
  while (cin >> u >> v >> w)
    kp.add(u, v + n, w);
  for (int u = 1; u <= n; ++u)
    kp.add(s, u, 0);
  for (int u = 1; u <= m; ++u)
    kp.add(u+n, t, 0);
  kp.calc();
	return 0;
}


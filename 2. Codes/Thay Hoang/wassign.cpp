#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
const ll inf = 1e16;
void file() {
  const string FILE_NAME = "wassign";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int n, m, s, t;
 struct edge {
  int u, v, w, cap;
  edge(int u, int v, int w, int c): u(u), v(v), w(w), cap(c) {}
};
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
struct karp {
  vector<int> adj[N];
  vector<edge> e;
  int match[N], cur[N], cont[N], par[N];
  ll dis[N], p[N];
  void add(int u, int v, int w) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, w, 1);
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, -w, 0);
  }
  #define wei(i) e[i].w + p[e[i].u] - p[e[i].v]
  priority_queue<pair<ll, int>> q;
  int bfs() {
    priority_queue<pair<ll, int>> q;
    fill(begin(dis), end(dis), inf);
    memset(cont, 0, sizeof(cont));
    q.emplace(0, s); dis[s] = 0;
    while (!q.empty()) {
      auto it = q.top();
      int u = it.second, d = -it.first; q.pop();
      if (d != dis[u]) continue;
      if (u != s) cont[par[u]] = 1;
      for (int i : adj[u]) if (e[i].cap == 1 && d + wei(i) < dis[e[i].v])
        dis[e[i].v] = d + wei(i), par[e[i].v] = i,
        q.emplace(-dis[e[i].v], e[i].v);
    }
    auto dt = dis[t];
    for (int u = s; u <= t; ++u)
      dis[u] += p[u] - p[s];
    for (int u = s; u <= t; ++u)
      p[u] = dis[u];
    return dt != inf;
  }
  ll cost = 0;
  int dfs(int u) {
    if (u == t)
      return 1;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int i = adj[u][cur[u]];
      if (e[i].cap == 0 || !cont[i]) continue;
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
    for (int u = s; u <= t; ++u)
      shuffle(adj[u].begin(), adj[u].end(), rng); 
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      for (int i : adj[s]) if (e[i].cap == 1)
        if (dfs(e[i].v))
          e[i].cap -= 1,
          e[i ^ 1].cap += 1;
    }
    cout << cost << '\n';
    for (int u = 1; u <= n; ++u) 
      cout << e[match[u]].v-n-1 << ' ';
  }
} kp;
int k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
  cin >> n; m = n, s = 0, t = n+m+1;
  for (int u = 1, w; u <= n; ++u)
    for (int v = 1; v <= m; ++v)
      cin >> w, kp.add(u, v+n, w);
  for (int u = 1; u <= n; ++u)
    kp.add(s, u, 0);
  for (int u = 1; u <= m; ++u)
    kp.add(u+n, t, 0);
  kp.calc();
	return 0;
}


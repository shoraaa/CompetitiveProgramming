#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 5;
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
struct dinic {
  vector<int> adj[N];
  vector<edge> e;
  int inq[N], match[N], cur[N], vis[N], cont[N];
  ll dis[N];
  void add(int u, int v, int w) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, w, 1);
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, -w, 0);
  }
  int que[int(4e6)];
  int fq, lq;
  int bfs() {
    fq = lq = 0;
    fill(begin(dis), end(dis), inf);
    que[fq] = s, inq[s] = 1, dis[s] = 0;
    while (fq <= lq) {
      int u = que[fq]; fq++; inq[u] = 0;
      for (int i : adj[u]) if (e[i].cap == 1 && dis[u] + e[i].w < dis[e[i].v]) {
        dis[e[i].v] = dis[u] + e[i].w;
        if (!inq[e[i].v]) 
          inq[e[i].v] = 1, que[++lq] = e[i].v;
      }
    }
    
    memset(vis, 0, sizeof(vis));
    memset(cont, 0, sizeof(cont));
    fq = lq = 0;
    que[fq] = s, inq[s] = 1;
    while (fq <= lq) {
      int u = que[fq]; fq++, inq[u] = 1;
      vis[u] = 1;
      for (int i : adj[u]) if (e[i].cap == 1 && !vis[e[i].v] && dis[u] + e[i].w == dis[e[i].v]) {
        cont[i] = 1;
        if (!inq[e[i].v]) 
          inq[e[i].v] = 1, que[++lq] = e[i].v;
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
      cout << e[match[u]].v - n - 1 << ' ';
  }
} din;
int k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
  cin >> n; m = n, s = 0, t = n+m+1;
  for (int u = 1, w; u <= n; ++u)
    for (int v = 1; v <= m; ++v)
      cin >> w, din.add(u, v+n, w);
  for (int u = 1; u <= n; ++u)
    din.add(s, u, 0);
  for (int u = 1; u <= m; ++u)
    din.add(u+n, t, 0);
  din.calc();
	return 0;
}


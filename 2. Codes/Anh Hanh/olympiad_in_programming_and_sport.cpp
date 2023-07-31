#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = 1e9;
const int N = 2e5 + 5;
int n, m, s, t, p_idx, s_idx;
struct dinic {
  struct edge {
    int u, v, c, w, f;
    edge(int u, int v, int w, int c): u(u), v(v), w(w), c(c), f(0) {}
  };
  vector<edge> e;
  vector<int> adj[N];
  void add(int u, int v, int w, int c) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, w, c);
    
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, -w, 0);
  }
  int cost = 0;
  int dis[N], inq[N], cur[N], par[N];
  int bfs() {
    queue<int> q;
    fill(begin(dis), end(dis), -inf);
    memset(inq, 0, sizeof(inq));
    q.emplace(s);
    dis[s] = 0; inq[s] = 1;
    while (!q.empty()) {
      int u = q.front(); q.pop(); inq[u] = 0;
      for (int i : adj[u]) if (e[i].c - e[i].f > 0 && dis[u] + e[i].w > dis[e[i].v]) {
        dis[e[i].v] = dis[u] + e[i].w;
        par[e[i].v] = i;
        if (!inq[e[i].v])
          q.emplace(e[i].v), inq[e[i].v] = 1;
      }
    }
    if (dis[t] == -inf)
      return 0;
    int u = t;
    while (u != s) {
      int i = par[u], v = e[i].u;
      e[i].f += 1, e[i ^ 1].f -= 1, cost += e[i].w;
      u = v;
    }
    return 1;
  }
  void min_cost() {
    while (bfs()) {}
    cout << cost << '\n';
    for (int i : adj[p_idx]) if (e[i ^ 1].f == e[i ^ 1].c)
      cout << e[i].v << ' ';
    cout << '\n';
    for (int i : adj[s_idx]) if (e[i ^ 1].f == e[i ^ 1].c)
      cout << e[i].v << ' ';
    cout << '\n';
  }
} din;
int a[N], b[N];
int p_cnt, s_cnt;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> p_cnt >> s_cnt; s = 0, t = n+3;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i)
    cin >> b[i];
  p_idx = n+1, s_idx = n+2;
  for (int u = 1; u <= n; ++u)
    din.add(s, u, 0, 1),
    din.add(u, p_idx, a[u], 1),
    din.add(u, s_idx, b[u], 1);
  din.add(p_idx, t, 0, p_cnt);
  din.add(s_idx, t, 0, s_cnt);
  din.min_cost();
	return 0;
}


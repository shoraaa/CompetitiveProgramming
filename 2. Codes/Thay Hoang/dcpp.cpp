#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e3 + 5;
void file() {
	const string FILE_NAME = "dcpp";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const ll inf = 1e15;
int p[N];
#define weight(i) e[i].w + p[e[i].u] - p[e[i].v]
int s, t;
vector<int> nLeft, nRight;
struct S {
  int u; ll d;
  S(int u, ll d): u(u), d(d) {}
  bool operator < (const S& v) const {
    return d > v.d;
  }
};
struct dinic {
  struct edge {
    int u, v, cap; ll w;
    edge(int u, int v, ll w, int c): u(u), v(v), w(w), cap(c){}
  };
  vector<edge> e;
  vector<int> adj[N];
  int cur[N], par[N];
  ll level[N];
  void add(int u, int v, ll w, int c = 1e9) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, w, c);
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, -w, 0);
  }
  ll cost = 0;
  int vis[N];
  int bfs() {
    fill(begin(level), end(level), inf);
    level[s] = 0;
    priority_queue<S> q;
    q.emplace(s, 0); 
    while (!q.empty()) {
      auto cur = q.top(); q.pop();
      if (cur.d != level[cur.u]) continue;
      for (int i : adj[cur.u]) cerr << e[i].w << ' ' << weight(i) << '\n';
      for (int i : adj[cur.u]) if (e[i].cap > 0 && cur.d + weight(i) < level[e[i].v]) 
        level[e[i].v] = cur.d + weight(i),
        par[e[i].v] = i,
        q.emplace(e[i].v, level[e[i].v]);
    }
    if (level[t] == inf)
      return 0;

    for (int u = 0; u <= t; ++u)
      level[u] += p[u] - p[s];
    for (int u = 0; u <= t; ++u)
      p[u] = level[u];
      
    int u = t;
    while (u != s) {
      int i = par[u];
      e[i].cap -= 1,
      e[i ^ 1].cap += 1,
      cost += e[i].w;
      u = e[i].u;
    }
    return 1;
  }

  ll min_cost() {
    while (bfs()) {}
    return cost;
  }
} din;
struct C {
  int v, w;
  C(int v, int w): v(v), w(w) {}
};
vector<C> adj[N];
int out[N], in[N];
ll dis[N];
int n, m;
ll total_w = 0;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
  cin >> n >> m;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w,
    total_w += w,
    adj[u].emplace_back(v, w),
    out[u]++, in[v]++;
  s = 0, t = n+1;
  for (int u = 1; u <= n; ++u)
    if (in[u] > out[u]) nLeft.emplace_back(u), din.add(s, u, 0, in[u] - out[u]);
    else if (in[u] < out[u]) nRight.emplace_back(u), din.add(u, t, 0, out[u] - in[u]);
  for (int u : nLeft) {
    priority_queue<S> q;
    q.emplace(u, 0);
    fill(begin(dis), end(dis), inf);
    dis[u] = 0;
    while (!q.empty()) {
      auto cur = q.top(); q.pop();
      if (cur.d != dis[cur.u]) continue;
      for (C& c : adj[cur.u]) if (cur.d + c.w < dis[c.v])
        dis[c.v] = cur.d + c.w,
        q.emplace(c.v, dis[c.v]);
    }
    for (int v : nRight)
      din.add(u, v, dis[v]);
  }
  cout << din.min_cost() + total_w;
	return 0;
}


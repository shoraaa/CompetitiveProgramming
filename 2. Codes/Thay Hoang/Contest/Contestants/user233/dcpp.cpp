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
    edge(int u, int v, ll w, int c): u(u), v(v), w(w), cap(c) {}
  };
  vector<edge> e;
  vector<int> adj[N];
  int cur[N], par[N], inq[N];
  ll level[N];
  void add(int u, int v, ll w, int c = 1e9) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, w, c);
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, -w, 0);
  }

  ll cost = 0;
  int bfs() {
    fill(begin(level), end(level), inf);
    memset(inq, 0, sizeof(inq));
    level[s] = 0;
    queue<int> q;
    q.emplace(s); inq[s] = 1;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      inq[u] = 0;
      for (int i : adj[u]) if (e[i].cap > 0 && level[u] + e[i].w < level[e[i].v]) {
        level[e[i].v] = level[u] + e[i].w;
        if (!inq[e[i].v])
          q.emplace(e[i].v), inq[e[i].v] = 1;
      }
    }
    return level[t] != inf;
  }
  int dfs(int u, int pushed) {
    if (u == t)
      return pushed;
    int sum = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int id = adj[u][cur[u]], v = e[id].v, push; 
      int cap = e[id].cap;
      if (cap <= 0 || level[u] + e[id].w != level[v]) continue;
      if (push = dfs(v, min(pushed, cap))) {
        e[id].cap -= push, 
        e[id ^ 1].cap += push;
        cost += ll(e[id].w) * push;
        sum += push;
        pushed -= push;
        if (pushed == 0)
          return sum;
      }
    }
    return sum;
  }

  ll min_cost() {
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      dfs(s, 1e9);
    }
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
vector<int> nLeft, nRight;
ll total_w = 0;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
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


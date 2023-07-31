#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 5, M = 1e6 + 5;
void file() {
	const string FILE_NAME = "dcpp";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int inf = 1e9;
const ll llinf = 1e18;
int n, m, s, t;
struct S {
  int u; ll d;
  S(int u, ll d): u(u), d(d) {}
  bool operator < (const S& v) const {
    return d > v.d;
  }
};
struct dinic {
  struct edge {
    int u, v, w, cap;
    edge(int u, int v, int w, int c): u(u), v(v), w(w), cap(c) {}
  };
  vector<edge> e;
  vector<int> adj[N];
  int cur[N];
  ll level[N];
  void add(int u, int v, int w, int c) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, w, c);
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, -w, 0);
  }

  ll cost = 0;
  int bfs() {
    fill(begin(level), end(level), inf);
    level[s] = 0;
    priority_queue<S> q;
    q.emplace(s, 0);
    while (!q.empty()) {
      auto cur = q.top(); q.pop();
      if (cur.d != level[cur.u]) continue;
      for (int i : adj[cur.u]) if (e[i].cap > 0 && cur.d + e[i].w < level[e[i].v])
        level[e[i].v] = cur.d + e[i].w,
        q.emplace(e[i].v, level[e[i].v]);
    }
    return level[t] != inf;
  }
  
  int dfs(int u, int pushed) {
    if (u == t)
      return pushed;
    ll sum = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int id = adj[u][cur[u]], v = e[id].v, push, cap = e[id].cap;
      if (cap <= 0 || level[u] + e[id].w != level[v]) continue;
      if (push = dfs(v, min(pushed, cap))) {
        e[id].cap -= push, 
        e[id ^ 1].cap += push,
        cost += ll(push) * e[id].w,
        sum += push, pushed -= push;
        if (pushed == 0)
          return sum;
      }
    }
    return sum;
  }

  ll min_cost() {
    int max_flow = 0;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      max_flow += dfs(s, inf);
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
  for (int u = 1; u <= n; ++u)
    if (in[u] > out[u]) nLeft.emplace_back(u);
    else if (in[u] < out[u]) nRight.emplace_back(u);
  s = 0, t = n+1;
  for (int u : nLeft)
    din.add(s, u, 0, inf);
  for (int u : nRight)
    din.add(u, t, 0, inf);
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
      din.add(u, v, dis[v], 1);
  }
  cout << din.min_cost() + total_w;
	return 0;
}


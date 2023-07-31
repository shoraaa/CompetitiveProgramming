#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
void file() {
	const string FILE_NAME = "walk";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const ll inf = 1e18;
int n, m, s, t;
struct dinic {
  struct edge {
    int u, v, w, cap;
    edge(int u, int v, int w, int c): u(u), v(v), w(w), cap(c) {}
  };
  vector<edge> e;
  vector<int> adj[N];
  int cur[N], inq[N], par[N];
  ll level[N];
  ll lwb;
  void add(int u, int v, int w, int c = 1) {
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
    q.emplace(s);
    memset(par, -1, sizeof(par));
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u == t) {
        while (u != s) {
          int i = par[u];
          e[i].cap -= 1,
          e[i ^ 1].cap += 1,
          cost += e[i].w;
          u = e[i].u;
        }
        return 1;
      }
      for (int i : adj[u]) if (e[i].cap > 0 && level[u] + e[i].w == level[e[i].v] && !~par[e[i].v]) 
        par[e[i].v] = i, q.emplace(e[i].v);
    }
    return 0;
  }

  void min_cost() {
    if (n == 1)
      return cout << 1, void();
    int max_flow = 0;
    while (int flow = bfs()) 
      max_flow += flow;
    if (max_flow != 2)
      return cout << -1, void();
    cout << cost << '\n';
    vector<int> nxt;
    for (int i : adj[1]) if (i % 2 == 0 && e[i].cap == 0)
      nxt.emplace_back(e[i].v);
    cout << 1 << ' ';
    while (nxt[0] != t) {
      cout << nxt[0] << ' ';
      for (int i : adj[nxt[0]]) if (i % 2 == 0 && e[i].cap == 0)
        nxt[0] = e[i].v;
    }
    vector<int> rev;
    while (nxt[1] != n) {
      rev.emplace_back(nxt[1]);
      reverse(adj[nxt[1]].begin(), adj[nxt[1]].end());
      for (int i : adj[nxt[1]]) if (i % 2 == 0 && e[i].cap == 0)
        nxt[1] = e[i].v;
    }
    reverse(rev.begin(), rev.end());
    for (int u : rev) cout << u << ' ';
    cout << 1 << '\n';
  }
} din;

int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
  cin >> n >> m; din.e.reserve(m * 4);
  s = 0, t = n+1;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w,
    din.add(u, v, w),
    din.add(v, u, w);
  din.add(s, 1, 0, 2);
  din.add(n, t, 0, 2);
  din.min_cost();
	return 0;
}


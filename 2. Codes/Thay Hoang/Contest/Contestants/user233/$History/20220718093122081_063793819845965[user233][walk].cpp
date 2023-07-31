#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e3 + 5;
void file() {
	const string FILE_NAME = "walk";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int inf = 1e9;
int n, m, s, t;
struct dinic {
  struct edge {
    int u, v, w, cap;
    edge(int u, int v, int w, int c): u(u), v(v), w(w), cap(c) {}
  };
  vector<edge> e;
  vector<int> adj[N];
  int cur[N], inq[N];
  ll level[N];
  ll lwb;
  void add(int u, int v, int w, int c = 1) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, w, c);
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, -w, 0);
  }

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
  ll cost = 0;
  int dfs(int u, int pushed) {
    if (u == t)
      return pushed;
    int flowed = 0;
    for (int i : adj[u]) {
      if (level[u] + e[i].w != level[e[i].v] || e[i].cap < 1) continue;
     if (int push = dfs(e[i].v, min(pushed, e[i].cap)))
        e[i].cap -= push,
        e[i ^ 1].cap += push,
        flowed += push, 
        cost += ll(push) * e[i].w,
        pushed -= push;
      if (pushed == 0)
        return flowed;
    }
    return flowed;
  }
  
  void min_cost() {
    int max_flow = 0;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      max_flow += dfs(s, inf);
    }
    assert(max_flow <= 2);
    if (max_flow != 2)
      return cout << -1, void();
    cout << cost << '\n';
    // vector<int> nxt;
    // for (int i : adj[1]) if (i % 2 == 0 && e[i].cap == 0)
      // nxt.emplace_back(e[i].v);
    // cout << 1 << ' ';
    // while (nxt[0] != t) {
      // cout << nxt[0] << ' ';
      // for (int i : adj[nxt[0]]) if (i % 2 == 0 && e[i].cap == 0)
        // nxt[0] = e[i].v;
    // }
    // vector<int> rev;
    // while (nxt[1] != n) {
      // rev.emplace_back(nxt[1]);
      // for (int i : adj[nxt[1]]) if (i % 2 == 0 && e[i].cap == 0)
        // nxt[1] = e[i].v;
    // }
    // reverse(rev.begin(), rev.end());
    // for (int u : rev) cout << u << ' ';
    // cout << 1 << '\n';
  }
} din;

int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
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


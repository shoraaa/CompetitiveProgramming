#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
const ll inf = 1e18;
void file() {
  const string FILE_NAME = "massign";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
int n, m, s, t;
struct dinic {
  struct edge {
    int u, v; ll cap;
    edge(int u, int v, int c): u(u), v(v), cap(c) {}
  };
  vector<edge> edges;
  vector<int> adj[N];
  int cur[N], level[N];
  ll lwb;
  stack<pair<int, int>> stk;
  void roll_back() {
    while (!stk.empty()) {
      int u = stk.top().first, v = stk.top().second; stk.pop();
      adj[u].pop_back(), adj[v].pop_back();
      edges.pop_back(), edges.pop_back();
    }
    for (int id = 0; id < edges.size(); ++id)
      edges[id].cap = id % 2 == 0;
  }
  void add(int u, int v, int c, int t = 0) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(u, v, c);
    adj[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0);
    if (t) stk.emplace(u, v);
  }
  int bfs() {
    queue<int> q;
    q.emplace(s);
    memset(level, -1, sizeof(level));
    level[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int id : adj[u]) if (!~level[edges[id].v] && edges[id].cap >= lwb)
        level[edges[id].v] = level[u] + 1, 
        q.emplace(edges[id].v);
    }
    return ~level[t];
  }
  ll dfs(int u, ll pushed) {
    if (u == t)
      return pushed;
    int sum = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int id = adj[u][cur[u]], v = edges[id].v, push; ll cap = edges[id].cap;
      if (cap < lwb || level[u] + 1 != level[v]) continue;
      if (push = dfs(v, min(pushed, cap))) 
        edges[id].cap -= push, 
        edges[id ^ 1].cap += push, 
        pushed -= push, sum += push;
      if (pushed == 0)
        return sum; 
    }
    return sum;
  }
  int max_flow(ll b) {
    ll res = 0; lwb = b;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      res += dfs(s, inf);
    }
    return res;
  }
  void trace() {
    vector<int> ans(m + 1);
    for (int u = 1; u <= n; ++u)
      for (int id : adj[u]) if (edges[id].v && !edges[id].cap)
        ans[edges[id].v - n] = u;
    for (int v = 1; v <= m; ++v)
      cout << ans[v] << ' ';
  }

  void reshuffle() {
    for (int u = 0; u < n; ++u)
      shuffle(adj[u].begin(), adj[u].end(), rng);
  }
} din;
int k;
int check(int x) {
  din.roll_back();
  for (int u = 1; u <= n; ++u)
    din.add(s, u, x, 1);
  int res = din.max_flow(1) == m;
  return res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
  cin >> n >> m; s = 0, t = n+m+1;
  int u, v; din.edges.reserve(m * 6);
  while (cin >> u >> v) 
    din.add(u, v + n, 1);
  for (int v = 1; v <= m; ++v)
    din.add(v + n, t, 1);
  int lo = 1, hi = m, mid, ans = m;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid))
      ans = mid,  
      hi = mid - 1;
    else
      lo = mid + 1;
  }
  cout << ans << '\n';
  check(ans), din.trace();
	return 0;
}


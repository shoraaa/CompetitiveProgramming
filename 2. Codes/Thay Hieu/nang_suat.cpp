#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 400 + 5;
const ll oo = 1e18;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
int n, m, s, t;
int wei[N][N];
struct dinic {
  struct edge {
    int u, v; ll cap;
    edge(int u, int v, int c): u(u), v(v), cap(c) {}
  };
  vector<edge> edges;
  vector<int> adj[N];
  int cur[N], level[N];
  ll lwb; stack<pair<int, int>> stk;
  void roll_back() {
    while (!stk.empty()) {
      int u = stk.top().first, v = stk.top().second; stk.pop();
      adj[u].pop_back(), adj[v].pop_back();
      edges.pop_back(), edges.pop_back();
    }
    for (int id = 0; id < edges.size(); ++id)
      edges[id].cap = id % 2 == 0;
  }
  void add(int u, int v, int t = 0) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(u, v, 1);
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
    int ans = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int id = adj[u][cur[u]], v = edges[id].v, push; ll cap = edges[id].cap;
      if (cap < lwb || level[u] + 1 != level[v]) continue;
      if (push = dfs(v, min(pushed, cap))) 
        edges[id].cap -= push, 
        edges[id ^ 1].cap += push, 
        pushed -= push, ans += push; 
      if (pushed == 0) 
        return ans;
    }
    level[u] = -1;
    return ans;
  }
  ll max_flow(ll b) {
    ll res = 0; lwb = b;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      res += dfs(s, oo);
    }
    return res;
  }
  ll max_flow() {
    ll res = 0;
    for (int i = 60; ~i; --i)
      res += max_flow(1LL << i);
    return res;
  }
  void reshuffle() {
    for (int u = 0; u < n; ++u)
      shuffle(adj[u].begin(), adj[u].end(), rng);
  }
  void trace() {
    vector<int> ans(n + 1);
    for (int u = 1; u <= n; ++u)
      for (int id : adj[u]) if (edges[id].v && !edges[id].cap)
        ans[u] = edges[id].v - n;
    for (int u = 1; u <= n; ++u)
      cout << ans[u] << ' ';
  }
} din;
int check(int lb) {
  din.roll_back();
  for (int u = 1; u <= n; ++u) for (int v = 1; v <= n; ++v)
    if (wei[u][v] >= lb) din.add(u, v + n, 1);
  return din.max_flow(1) == n;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; s = 0, t = n*2+1;
  int u, v; din.edges.reserve(n * n * 2);
  for (int u = 1; u <= n; ++u)
    for (int v = 1; v <= n; ++v)
      cin >> wei[u][v];
  for (int u = 1; u <= n; ++u)
    din.add(s, u);
  for (int v = 1; v <= n; ++v)
    din.add(v + n, t);
  int lo = 1, hi = 20000, mid, ans = 1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid))
      ans = mid,
      lo = mid + 1;
    else
      hi = mid - 1;  
  }
  cout << ans << '\n'; 
  check(ans), din.trace();
  
	return 0;
}


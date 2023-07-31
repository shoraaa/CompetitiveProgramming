#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 50 + 5;
const ll llinf = 1e18;
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
  void add(int u, int v, int c) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(u, v, c);
    adj[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0);
  }
  void reset() {
    for (int u = s; u <= t; ++u)   
      adj[u].clear();
    edges.clear();
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
    ll sum = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int id = adj[u][cur[u]], v = edges[id].v, push; 
      ll cap = edges[id].cap;
      if (cap < lwb || level[u] + 1 != level[v]) continue;
      if (push = dfs(v, min(pushed - sum, cap))) {
        edges[id].cap -= push, 
        edges[id ^ 1].cap += push;
        sum += push;
        if (sum == pushed)
          return sum;
      }
    }
    return sum;
  }
  ll max_flow(ll b) {
    ll res = 0; lwb = b;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      while (ll push = dfs(s, llinf))
        res += push;
    }
    return res;
  }
  ll max_flow() {
    ll res = 0;
    for (int i = 60; ~i; --i)
      res += max_flow(1LL << i);
    return res;
  }
} din;
int x;
vector<tuple<int, int, ll>> edges;
const ld eps = 1e-9;
ll divi(int w, ld x) {
  ll lo = 0, hi = 1e9, mid, ans = 0;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (mid * x <= w)
      ans = mid,
      lo = mid + 1;
    else
      hi = mid - 1;
  }
  return ans;
}
int check(ld mid) {
  din.reset();
  int u, v; ll w;
  for (auto& t : edges) {
    tie(u, v, w) = t;
    ll nw = divi(w, mid);
    if ((nw+1) * mid <= w + eps) nw++;
    din.add(u, v, nw);
  } 
  return din.max_flow() >= x;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> x; s = 0, t = n-1;
  for (int i = 0, u, v, c; i < m; ++i) {
    cin >> u >> v >> c; u--, v--;
    edges.emplace_back(u, v, c);
  }
  ld lo = 0, hi = 1e9, mid, ans = 0;
  for (int i = 0; i < 1000; ++i) {
    mid = (lo + hi) / 2;
    if (check(mid)) 
      ans = mid,
      lo = mid;
    else
      hi = mid;
  }
  cout << fixed << setprecision(9) << ans * x;
	return 0;
}


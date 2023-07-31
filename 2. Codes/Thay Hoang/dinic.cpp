#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e3 + 5;
const ll oo = 1e18;
int n;
struct dinic {
  struct edge {
    int u, v; ll cap;
    edge(int u, int v, int c): u(u), v(v), cap(c) {}
  };
  vector<edge> edges;
  vector<int> adj[N];
  int cur[N], level[N];
  int s, t; ll lwb;
  void add(int u, int v, int c) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(u, v, c);
    adj[v].emplace_back(edges.size());
    edges.emplace_back(v, u, c);
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
      if (push = dfs(v, min(pushed, cap))) {
        edges[id].cap -= push, 
        edges[id ^ 1].cap += push;
        sum += push, pushed -= push;
        if (pushed == 0)
          return sum;
      }
    }
    return sum;
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
    for (int i = 45; ~i; --i)
      res += max_flow(1LL << i);
    return res;
  }
} din;

int m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; din.edges.reserve(m * 4);
  din.s = 0, din.t = n-1;
  for (int i = 0, u, v, c; i < m; ++i)
    cin >> u >> v >> c, u--, v--,
    din.add(u, v, c);
  cout << din.max_flow();
	return 0;
}


#include<bits/stdc++.h>
#define cout cerr
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "voi";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3e5 + 5;
const ll llinf = 1e18;
int n, m, s, t;
struct dinic {
  struct edge {
    int u, v; ll f, c;
    edge(int u, int v, ll c): u(u), v(v), c(c), f(0) {}
  };
  vector<edge> e;
  vector<int> adj[N];
  void add(int u, int v, ll c) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, c);
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, 0);
  }
  void reset() {
    for (int i = s; i <= t; ++i) adj[i].clear();
    e.clear();
  }
  int dis[N];
  int bfs() {
    queue<int> q;
    fill(begin(dis), end(dis), -1);
    q.emplace(s); dis[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop(); 
      for (int i : adj[u]) if (e[i].c - e[i].f > 0 && !~dis[e[i].v])
        dis[e[i].v] = dis[u] + 1,
        q.emplace(e[i].v);
    }
    return ~dis[t];
  }
  int cur[N];
  ll dfs(int u, ll flow) {
    if (u == t) return flow;
    ll pushed = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int i = adj[u][cur[u]];
      if (e[i].c - e[i].f <= 0 || dis[u] + 1 != dis[e[i].v]) continue;
      if (int push = dfs(e[i].v, min(flow, e[i].c - e[i].f)))
        e[i].f += push, e[i^1].f -= push,
        pushed += push, flow -= push;
      if (flow == 0) break;
    }
    return pushed;
  }
  ll max_flow() {
    ll flow = 0;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      flow += dfs(s, llinf);
    }
    return flow;
  }
} din;
string str; vector<pair<int, int>> hate;
ll calc(char x, char y) {
  din.reset();
  for (int u = 1; u <= n; ++u)
    if (str[u] == x) din.add(s, u, 1);
    else if (str[u] == y) din.add(u, t, 1);
  for (auto& p : hate) {
    int u = p.first, v = p.second;
    if (str[u] == x && str[v] == y)
      din.add(u, v, llinf);
    swap(u, v);
    if (str[u] == x && str[v] == y)
      din.add(u, v, llinf);
  }
  return din.max_flow();
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
  cin >> n >> str >> m, s = 0, t = n+1, str = ' ' + str;
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v,
    hate.emplace_back(u, v);
  cout << min({calc('R', 'G'), calc('G', 'B'), calc('R', 'B')});
	return 1;
}


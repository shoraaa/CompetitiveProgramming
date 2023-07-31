#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll llinf = 1e18;
const int N = 2e5 + 5;
void file() {
	const string FILE_NAME = "stadium";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int n, m, s, t;
struct dinic {
  struct edge {
    int u, v; ll c;
    edge(int u, int v, ll c): u(u), v(v), c(c) {}
  };
  vector<edge> e;
  vector<int> adj[N];
  void add(int u, int v, ll c) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, c);
    
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, 0);
  }
  ll dis[N];
  int cur[N];
  int bfs() {
    queue<int> q;
    fill(begin(dis), end(dis), -1);
    q.emplace(s);
    dis[s] = 0; 
    while (!q.empty()) {
      int u = q.front(); q.pop(); 
      for (int i : adj[u]) if (e[i].c > 0 && !~dis[e[i].v]) 
        dis[e[i].v] = dis[u] + 1,
        q.emplace(e[i].v);
    }
    return ~dis[t];
  }
  ll dfs(int u, ll flow) {
    if (u == t) return flow;
    ll pushed = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int i = adj[u][cur[u]];
      if (e[i].c <= 0 || dis[u] + 1 != dis[e[i].v]) continue;
      if (int push = dfs(e[i].v, min(flow, e[i].c)))
        e[i].c -= push, e[i^1].c += push,
        flow -= push, pushed += push;
      if (flow == 0) break;
    }
    return pushed;
  }
  void min_cut() {
    ll flow = 0;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      flow += dfs(s, llinf);
    }
    cout << flow << '\n';
    vector<int> lef, rig; bfs();
    for (int u = 1; u <= n; ++u) if (dis[u] == -1)
      lef.emplace_back(u);
    for (int v = 1; v <= m; ++v) if (dis[v+n] != -1)
      rig.emplace_back(v);
    cout << lef.size() << ' ';
    for (int u : lef) cout << u << ' ';
    cout << '\n' << rig.size() << ' ';
    for (int u : rig) cout << u << ' ';
  }
} din;
string str[N];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
  int T;
  cin >> T >> n >> m; s = 0, t = n+m+1;
  for (int u = 1, c; u <= n; ++u)
    cin >> c, din.add(s, u, c);
  for (int u = 1, c; u <= m; ++u)
    cin >> c, din.add(u+n, t, c);
  for (int i = 1; i <= n; ++i) 
    cin >> str[i], str[i] = ' ' + str[i];
  for (int u = 1; u <= n; ++u) for (int v = 1; v <= m; ++v)
    if (str[u][v] == '1') din.add(u, v+n, llinf);
  din.min_cut();
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = 1e9;
const int N = 3e5 + 5;
void file() {
	const string FILE_NAME = "rooks";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int n, q, s, t, sum = 0;
int tr[N], tc[N], ur[N], uc[N];
vector<pair<int, int>> cent;
int row[N], col[N], vis[55][55];
struct dinic {
  struct edge {
    int u, v, c, w, f;
    edge(int u, int v, int w, int c): u(u), v(v), w(w), c(c), f(0) {}
  };
  vector<edge> e;
  vector<int> adj[N];
  void add(int u, int v, int w, int c) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, w, c);
    
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, -w, 0);
  }
  int cost = 0;
  int dis[N], inq[N], cur[N], par[N];
  int bfs() {
    queue<int> q;
    fill(begin(dis), end(dis), inf);
    memset(inq, 0, sizeof(inq));
    q.emplace(s);
    dis[s] = 0; inq[s] = 1;
    while (!q.empty()) {
      int u = q.front(); q.pop(); inq[u] = 0;
      for (int i : adj[u]) if (e[i].c - e[i].f > 0 && dis[u] + e[i].w < dis[e[i].v]) {
        dis[e[i].v] = dis[u] + e[i].w;
        par[e[i].v] = i;
        if (!inq[e[i].v])
          q.emplace(e[i].v), inq[e[i].v] = 1;
      }
    }
    if (dis[t] == inf)
      return 0;
    int u = t;
    while (u != s) {
      int i = par[u], v = e[i].u;
      e[i].f += 1, e[i ^ 1].f -= 1, cost += e[i].w;
      u = v;
    }
    return 1;
  }
  void min_cost() {
    int flow = 0;
    while (int push = bfs()) 
      flow += push;
    if (flow != n || n-cost != sum) 
      return cout << "NO", void();
    cout << "YES\n";
    vector<int> ans(n + 1);
    for (auto& p : cent) {
      int u_in = p.first, u_out = p.second;
      vector<int> r, c;
      for (int i : adj[u_in]) if (e[i].v != u_out && e[i^1].f == e[i^1].c)
        r.emplace_back(tr[e[i].v]); 
      for (int i : adj[u_out]) if (e[i].v != u_in && e[i].f == e[i].c)
        c.emplace_back(tc[e[i].v]);
      assert(r.size() == c.size());
      for (int i = 0; i < r.size(); ++i)
        ans[r[i]] = c[i], ur[r[i]] = 1, uc[c[i]] = 1;
    }
    for (int i = 1; i <= n; ++i) if (!ur[i]) {
      for (int id : adj[row[i]]) if (e[id].f == e[id].c) {
        ans[i] = tc[e[id].v]; break;
      }
    }
    for (int i = 1; i <= n; ++i)
      cout << ans[i] << ' ';
  }
} din;
int id = 0;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
  cin >> n >> q; s = id++;
  for (int i = 1; i <= n; ++i) row[i] = id++, tr[row[i]] = i;
  for (int i = 1; i <= n; ++i) col[i] = id++, tc[col[i]] = i;
  for (int b, l, t, r, c; q--;) {
    cin >> b >> l >> t >> r >> c; sum += c;
    int u_in = id++, u_out = id++;
    cent.emplace_back(u_in, u_out);
    din.add(u_in, u_out, 0, c); 
    for (int i = b; i <= t; ++i) for (int j = l; j <= r; ++j)
      din.add(row[i], u_in, 0, 1),
      din.add(u_out, col[j], 0, 1),
      vis[i][j] = 1;
  }
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j)
    if (!vis[i][j]) din.add(row[i], col[j], 1, 1);
  t = id++;
  
  for (int i = 1; i <= n; ++i)
    din.add(s, row[i], 0, 1);
  for (int i = 1; i <= n; ++i)
    din.add(col[i], t, 0, 1);
    
  din.min_cost();
	return 0;
}


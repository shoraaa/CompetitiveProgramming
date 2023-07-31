#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = 1e9;
const int N = 500 + 5;
int n, m, s, t;
struct dinic {
  struct edge {
    int u, v, c, w;
    edge(int u, int v, int w, int c): u(u), v(v), w(w), c(c) {}
  };
  vector<edge> e;
  vector<int> adj[N*N];
  void add(int u, int v, int w, int c) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, w, c);
    
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, -w, 0);
  }
  int cost = 0;
  int dis[N*N], inq[N*N], cur[N*N], par[N*N];
  int bfs() {
    queue<int> q;
    fill(begin(dis), end(dis), inf);
    memset(inq, 0, sizeof(inq));
    q.emplace(s);
    dis[s] = 0; inq[s] = 1;
    while (!q.empty()) {
      int u = q.front(); q.pop(); inq[u] = 0;
      for (int i : adj[u]) if (e[i].c > 0 && dis[u] + e[i].w < dis[e[i].v]) {
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
      e[i].c -= 1, e[i ^ 1].c += 1, cost += e[i].w;
      u = v;
    }
    return 1;
  }
  int min_cost() {
    while (bfs()) {}
    return cost;
  }
} din;
int a[N][N], col[N][N];
vector<pair<int, int>> pos[2];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; s = 0, t = n*m+1;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) 
    cin >> a[i][j], col[i][j] = (i + j) & 1,
    pos[col[i][j]].emplace_back(i, j);
  for (auto& p : pos[0]) {
    int u = p.first*m+p.second+1;
    din.add(s, u, 0, 1);
  }
  for (auto& p1 : pos[0]) for (auto& p2 : pos[1]) {
    int u = p1.first*m+p1.second+1, v = p2.first*m+p2.second+1;
    if (abs(p1.first - p2.first) + abs(p1.second - p2.second) == 1)
      din.add(u, v, a[p1.first][p1.second] != a[p2.first][p2.second], 1);
  }
  for (auto& p : pos[1]) {
    int u = p.first*m+p.second+1;
    din.add(u, t, 0, 1);
  }
  cout << din.min_cost();
	return 0;
}


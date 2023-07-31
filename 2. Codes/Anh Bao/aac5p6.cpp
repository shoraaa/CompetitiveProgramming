#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
struct State {
  int u; ll d;
  State(int u, ll d): u(u), d(d) {}
  bool operator < (const State& s) const {
    return d > s.d;
  }
};
priority_queue<State> q;
int a[N]; ll dis[N];
vector<int> adj[N];
int n, k;
struct Centroid {
  vector<int> vert[N];
  int siz[N], par[N], vis[N], cur[N], dep[N], h[20][N];
  int find(int u, int p, int s) {
    for (int v : adj[u]) if (!vis[v] && v != p)
      if (siz[v] > s) return find(v, u, s);
    return u;
  }
  int size(int u, int p = -1) {
    siz[u] = 1, par[u] = p;
    for (int v : adj[u]) if (!vis[v] && v != p)
      siz[u] += size(v, u);
    return siz[u];
  }
  void solve(int u = 0, int p = -1, int d = 0) {
    int c = find(u, -1, size(u) / 2);
    par[c] = p, cur[c] = 0, dep[c] = d;
    queue<pair<int, int>> q;
    q.emplace(c, -1);
    while (!q.empty()) {
      int u = q.front().first, p = q.front().second; q.pop();
      vert[c].emplace_back(u);
      for (int v : adj[u]) if (!vis[v] && v != p)
        q.emplace(v, u), h[d][v] = h[d][u] + 1;
    }
   vis[c] = 1;
    for (int v : adj[c]) if (!vis[v])
      solve(v, c, d + 1);
  }
  void update(int u, ll d) {
    for (int v = u; ~v; v = par[v]) {
      int i = dep[v];
      for (; cur[v] < vert[v].size(); ++cur[v]) {
        int t = vert[v][cur[v]];
        if (h[i][u] + h[i][t] > k) break;
        if (d + a[t] < dis[t])
          dis[t] = d + a[t],
          q.emplace(t, dis[t]);
      }
    }
  }
  
} ct;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v), 
    adj[v].emplace_back(u);
  ct.solve();
  memset(dis, 0x3f, sizeof(dis));
  q.emplace(0, 0);
  dis[0] = 0; a[0] = 0;
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    if (s.d != dis[s.u]) continue;
    ct.update(s.u, s.d);
  }
  for (int v = 0; v < n; ++v)
    cout << dis[v] << " \n"[v == n-1];
	return 0;
}


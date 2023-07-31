#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5, inf = 1e9;
vector<int> adj[N];
int dep[N];
int n, d;
struct centroid {
  int par[N], siz[N], val[N], h[N];
  centroid() {
    memset(val, 0x3f, sizeof(val));
  }
  int size(int u, int e) {
    siz[u] = 1;
    for (int v : adj[u]) if (v != e && !par[v])
      siz[u] += size(v, u);
    return siz[u];
  }
  int find(int u, int e, int s) {
    for (int v : adj[u]) if (v != e && !par[v] && siz[v] > s / 2)
      return find(v, u, s);
    return u;
  }
  int dis[20][N];
  void dfs(int u, int e, int c, int d) {
    dis[h[c]][u] = d;
    for (int v : adj[u]) if (v != e && !par[v])
      dfs(v, u, c, d + 1);
  }
  void decompose(int u = 1, int e = 0) {
    u = find(u, e, size(u, e));
    if (e == 0) par[u] = -1;
    else par[u] = e, h[u] = h[e] + 1;
    dfs(u, e, u, 0);
    for (int v : adj[u]) if (!par[v]) 
      decompose(v, u);
  }
  void update(int u) {
    for (int p = u; ~p; p = par[p]) 
      val[p] = min(val[p], dis[h[p]][u]);
  }
  int get(int u) {
    int res = inf;
    for (int p = u; ~p; p = par[p])
      res = min(res, dis[h[p]][u] + val[p]);
    return res;
  }
} ct;
void dfs(int u = 1, int p = 0) {
  for (int v : adj[u]) if (v != p)
    dep[v] = dep[u] + 1, dfs(v, u);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> d;
  for (int i = 2, p; i <= n; ++i)
    cin >> p, p++,
    adj[i].emplace_back(p),
    adj[p].emplace_back(i);
  ct.decompose(); dfs();
  vector<int> vert(n);
  iota(vert.begin(), vert.end(), 1);
  sort(vert.begin(), vert.end(), [&](int u, int v) {
    return dep[u] > dep[v];
  });
  int res = 0;
  for (int v : vert) {
    if (ct.get(v) >= d) ct.update(v), res++;
  }
  cout << res;
	return 0;
}
 
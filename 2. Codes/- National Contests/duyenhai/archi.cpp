#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
struct S {
  int x, y, u, v, id; ll s;
  S(int x, int y, int u, int v, int id): 
    x(x), y(y), u(u), v(v), id(id), s(1LL * (u-x) * (v-y)) {}
};
vector<S> a, b;
vector<int> G[N];
int dep[N], par[N][20];
int n, m;
void dfs(int u = 0, int e = -1) {
  if (e != -1) {
    dep[u] = dep[e] + 1, par[u][0] = e;
    for (int k = 1; k < 20; ++k)
      par[u][k] = par[par[u][k-1]][k-1];
  }
  for (int v : G[u]) if (v != e)
    dfs(v, u);
}
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = 19; ~k; --k)
    if (dep[par[u][k]] <= dep[v]) u = par[u][k];
  if (u == v) return u;
  for (int k = 19; ~k; --k) if (par[u][k] != par[v][k]) 
    u = par[u][k], v = par[v][k];
  return par[u][0];
}
int cont(int x, int y) {
  for (int i = 0; i <= n; ++i) 
    if (a[i].x < x && a[i].u > x && 
        a[i].y < y && a[i].v > y) return a[i].id;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; a.reserve(n + 1), b.reserve(m);
  a.emplace_back(-1e9, -1e9, 1e9, 1e9, 0);
  for (int i = 1, x, y, u, v; i <= n; ++i) 
    cin >> x >> y >> u >> v,
    a.emplace_back(x, y, u, v, i);
  sort(a.begin(), a.end(), [&](S& u, S& v) {
    return u.s < v.s;
  });
  for (int i = 0; i < n; ++i) {
    int j = i+1; 
    for (; j <= n; ++j) 
      if (a[j].x < a[i].x && a[j].u > a[i].u && 
          a[j].y < a[i].y && a[j].v > a[i].v) break;
    G[a[i].id].emplace_back(a[j].id),
    G[a[j].id].emplace_back(a[i].id);
  }
  dfs();
  for (int i = 0, x1, y1, x2, y2; i < m; ++i) {
    cin >> x1 >> y1 >> x2 >> y2;
    int u = cont(x1, y1), v = cont(x2, y2);
    cout << dep[u] + dep[v] - 2 * dep[lca(u, v)] << '\n';
  }
	return 0;
}


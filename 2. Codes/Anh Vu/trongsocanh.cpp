#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
struct E {
  int u, v, w, i;
  bool operator < (const E& e) {
    return w < e.w;
  }
} a[N];
struct C {
  int v, i;
  C(int v, int i): v(v), i(i) {}
};
vector<C> G[N];
int lin[N], siz[N], nxt[N];
int res[N], mst[N], dep[N], pe[N], par[N][20], val[N][20];
int n, m;
int find(int u) {
  if (u == lin[u]) return u;
  return lin[u] = find(lin[u]);
}
int unite(int u, int v) {
  u = find(u), v = find(v);
  if (u == v) return 0;
  int nxtv = nxt[v];
  if (siz[u] < siz[v]) swap(u, v);
  lin[v] = u, siz[u] += siz[v], nxt[u] = nxtv;
  return 1;
}
pair<int, int> get(int u, int v) {
  int res = -2e9;
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = 19; ~k; --k) if (dep[u] - (1 << k) >= dep[v]) 
    res = max(res, val[u][k]), u = par[u][k];
  if (u == v) return {v, res};
  for (int k = 19; ~k; --k) if (par[u][k] != par[v][k])
    res = max(res, max(val[u][k], val[v][k])), 
    u = par[u][k], v = par[v][k];
  return {par[u][0], max(res, max(val[u][0], val[v][0]))};
}
void update(int u, int v, int c, int w) {
  for (u = nxt[find(u)]; dep[u] > dep[c]; u = nxt[find(u)]) 
    res[pe[u]] = w, unite(u, par[u][0]);
  for (v = nxt[find(v)]; dep[v] > dep[c]; v = nxt[find(v)]) 
    res[pe[v]] = w, unite(v, par[v][0]);
}
void build(int u = 0, int e = -1) {
  if (e != -1) {
    par[u][0] = a[e].u ^ a[e].v ^ u;
    val[u][0] = a[e].w; 
    dep[u] = dep[par[u][0]] + 1;
    pe[u] = a[e].i;
    for (int k = 1; k < 20; ++k)
      par[u][k] = par[par[u][k-1]][k-1],
      val[u][k] = max(val[par[u][k-1]][k-1], val[u][k-1]);
  }
  for (C& c : G[u]) if (c.i != e)
    build(c.v, c.i);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < m; ++i)
    cin >> a[i].u >> a[i].v >> a[i].w, 
    a[i].u--, a[i].v--, a[i].i = i;
  sort(a, a + m);
  for (int i = 0; i < n; ++i)
    lin[i] = i, siz[i] = 1;
  for (int i = 0; i < m; ++i) if (unite(a[i].u, a[i].v))
    G[a[i].u].emplace_back(a[i].v, i), 
    G[a[i].v].emplace_back(a[i].u, i),
    mst[i] = 1;
  memset(val, -0x3f, sizeof(val));
  build();
  for (int i = 0; i < n; ++i)
    lin[i] = i, nxt[i] = i, siz[i] = 1;
  for (int i = 0; i < m; ++i) if (!mst[i]) {
    auto lca = get(a[i].u, a[i].v);
    res[a[i].i] = lca.second;
    update(a[i].u, a[i].v, lca.first, a[i].w);
  }
  for (int i = 0; i < m; ++i)
    cout << res[i]-1 << ' ';
	return 0;
}


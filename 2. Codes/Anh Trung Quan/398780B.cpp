#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
struct Adjacent {
  int v, i;
  Adjacent(int v, int i): v(v), i(i) {}
};
vector<Adjacent> adj[N];
int siz[N], dep[N], nxt[N], par[N], low[N], cur[N];
int size(int u, int p = -1) {
  siz[u] = 1, par[u] = p;
  for (auto& c : adj[u]) if (c.v != p) {
    low[c.i] = c.v;
    siz[u] += size(c.v, u);
    if (adj[u][0].v == p || siz[u] > siz[adj[u][0].v])
      swap(adj[u][0], c);
  }
  return siz[u];
}
void hld(int u, int p = -1) {
  for (auto& c : adj[u]) if (c.v != p) {
    nxt[c.v] = c.v == adj[u][0].v ? nxt[u] : c.v;
    dep[c.v] = dep[u] + 1;
    hld(c.v, u);
  }
}
struct cmp {
  bool operator () (int u, int v) const {
    return dep[u] > dep[v];
  }
};
set<int, cmp> s[N];
void update(int u) {
  if (!s[nxt[u]].count(u))
    s[nxt[u]].insert(u);
  else s[nxt[u]].erase(u);
}
int get(int u) {
  for (; ~u; u = par[nxt[u]]) if (!s[nxt[u]].empty()) {
    auto it = s[nxt[u]].lower_bound(u);
    if (it != s[nxt[u]].end()) return *it;
  }
  return 0;
}
int f[N], ans[N];
int n, m, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	if (fopen("past_battle.inp", "r"))
	  freopen("past_battle.inp", "r", stdin),
	  freopen("past_battle.out", "w", stdout);
  cin >> n >> m >> q;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v, i),
    adj[v].emplace_back(u, i);
  size(0), hld(0);
  for (int v = 0; v < n; ++v)
    update(v), f[v] = ans[v] = 1;
  for (int i = 0, id, v, nxt; i < m; ++i) {
    cin >> id, id--; v = low[id];
    if (!cur[id]) update(v), f[get(v)] += f[v], ans[get(v)] += f[v], f[v] = 0;
    else ans[v] = ans[get(v)], update(v);
    cur[id] ^= 1;
  }
  for (int i = 0, v; i < q; ++i)
    cin >> v, v--,
    cout << ans[get(v)] << '\n';
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
int n, q;
vector<int> adj[N];
int siz[N], dep[N], nxt[N], par[N];
int size(int u, int p = -1) {
  siz[u] = 1, par[u] = p;
  for (int& v : adj[u]) if (v != p) {
    siz[u] += size(v, u);
    if (adj[u][0] == p || siz[u] > siz[adj[u][0]])
      swap(adj[u][0], v);
  }
  return siz[u];
}
void hld(int u, int p = -1) {
  for (int v : adj[u]) if (v != p) {
    nxt[v] = v == adj[u][0] ? nxt[u] : v;
    dep[v] = dep[u] + 1;
    hld(v, u);
  }
}
struct cmp {
  bool operator () (int u, int v) const {
    return dep[u] < dep[v];
  }
};
set<int, cmp> s[N];
void update(int u) {
  if (!s[nxt[u]].count(u))
    s[nxt[u]].insert(u);
  else s[nxt[u]].erase(u);
}
int get(int u) {
  int res = -1;
  for (; ~u; u = par[nxt[u]]) 
    if (!s[nxt[u]].empty() && dep[*s[nxt[u]].begin()] <= dep[u]) 
      res = *s[nxt[u]].begin() + 1;
  return res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  size(0), hld(0);
  for (int i = 0, t, v; i < q; ++i) {
    cin >> t >> v, v--;
    if (t == 0) update(v);
    else cout << get(v) << '\n';
  }
	return 0;
}


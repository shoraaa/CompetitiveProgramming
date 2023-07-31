#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e4 + 5;
const int inf = 1e9;
struct SegmentTree {
  int n, x, y, v, res;
  vector<pair<int, int>> st;
  vector<int> lz;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2), lz(n * 2) {}
  void negate(pair<int, int>& p) {
    swap(p.first, p.second), p.first *= -1, p.second *= -1;
  }
  void push(int k, int lc, int rc) {
    if (!lz[k]) return; lz[k] = 0;
    negate(st[lc]), lz[lc] ^= 1;
    negate(st[rc]), lz[rc] ^= 1;
  }
  void negate(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y)
      return negate(st[k]), lz[k] ^= 1, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    negate(lc, l, m), negate(rc, m+1, r);
    st[k].first = max(st[lc].first, st[rc].first);
    st[k].second = min(st[lc].second, st[rc].second);
  }
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y)
      return res = max(res, st[k].first), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    get(lc, l, m), get(rc, m+1, r);
  }
  void set(int k, int l, int r) {
    if (l > x || r < x) return;
    if (l == r)
      return st[k].first = st[k].second = v, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    set(lc, l, m), set(rc, m+1, r);
    st[k].first = max(st[lc].first, st[rc].first);
    st[k].second = min(st[lc].second, st[rc].second);
  }
  void negate(int l, int r) {
    x = l, y = r;
    negate(1, 0, n-1);
  }
  void set(int i, int v) {
    x = i, this->v = v;
    set(1, 0, n-1);
  }
  int get(int l, int r) {
    x = l, y = r, res = -inf;
    get(1, 0, n-1);
    return res;
  }
} st;
struct AdjacentEdge {
  int v, i;
  AdjacentEdge(int v, int i): v(v), i(i) {};
};
vector<AdjacentEdge> adj[N];
int siz[N], par[N], nxt[N], in[N], dep[N], idx[N], e[N];
int size(int u, int p = -1) {
  siz[u] = 1, par[u] = p;
  for (auto& c : adj[u]) if (c.v != p) {
    siz[u] += size(c.v, u);
    if (adj[u][0].v == p || siz[c.v] > siz[adj[u][0].v])
      swap(c, adj[u][0]);
  }
  return siz[u];
}
int t;
void hld(int u, int p = -1) {
  in[u] = t++; 
  for (auto& c : adj[u]) if (c.v != p) {
    nxt[c.v] = c.v == adj[u][0].v ? nxt[u] : c.v;
    dep[c.v] = dep[u] + 1, idx[c.i] = c.v;
    hld(c.v, u);
    st.set(in[c.v], e[c.i]);
  }
}
int query(int u, int v) {
  if (u == v) 
    return 0;
  int res = -inf;
  for (; nxt[u] != nxt[v];) {
    if (dep[nxt[u]] < dep[nxt[v]]) swap(u, v);
    res = max(res, st.get(in[nxt[u]], in[u]));
    u = par[nxt[u]];
  }
  if (dep[u] > dep[v]) swap(u, v);
  res = max(res, st.get(in[u] + 1, in[v]));
  return res;
}
void update(int u, int v) {
  for (; nxt[u] != nxt[v];) {
    if (dep[nxt[u]] < dep[nxt[v]]) swap(u, v);
    st.negate(in[nxt[u]], in[u]);
    u = par[nxt[u]];
  }
  if (dep[u] > dep[v]) swap(u, v);
  st.negate(in[u] + 1, in[v]);
}
void change(int u, int v) {
  st.set(in[u], v);
}
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n; t = 0;
    for (int i = 0, u, v, w; i < n-1; ++i)
      cin >> u >> v >> w, u--, v--,
      adj[u].emplace_back(v, i),
      adj[v].emplace_back(u, i),
      e[i] = w;
    st = SegmentTree(n);
    size(0), hld(0);
    string s;
    int u, v;
    while (cin >> s) {
      if (s[0] == 'D') break;
      cin >> u >> v;
      if (s[0] == 'Q') 
        u--, v--, cout << query(u, v) << '\n';
      else if (s[0] == 'N')
        u--, v--, update(u, v);
      else 
        u--, change(idx[u], v);
    }
    for (int u = 0; u < n; ++u)
      adj[u].clear();
  }
	return 0;
}


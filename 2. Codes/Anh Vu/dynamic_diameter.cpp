#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
#define int ll
const ll inf = 1e17;
struct Edge {
  int u, v, w;
  Edge(int u, int v, int w): u(u), v(v), w(w) {}
  int adj(int t) {
    return u + v - t;
  }
};
pair<ll, int> depth[N];
ll lpath[N];
struct Depth {
  int n, x, y;
  ll v;
  pair<ll, int> res;
  vector<ll> lz;
  vector<pair<ll, int>> st;
  Depth() {}
  Depth(int n): n(n), st(n * 2), lz(n * 2) { build(1, 0, n-1); }
  void build(int k, int l, int r) {
    if (l == r) 
      return st[k] = depth[l], void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    build(lc, l, m), build(rc, m+1, r);
    st[k] = max(st[lc], st[rc]);
  }
  void push(int k, int lc, int rc) {
    ll w = lz[k]; lz[k] = 0;
    st[lc].first += w, lz[lc] += w,
    st[rc].first += w, lz[rc] += w;
  }
  void update(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return st[k].first += v, lz[k] += v, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    update(lc, l, m), update(rc, m+1, r);
    st[k] = max(st[lc], st[rc]);
  }
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return res = max(res, st[k]), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    get(lc, l, m), get(rc, m+1, r);
  }
  void add(int l, int r, ll w) {
    x = l, y = r, v = w;
    update(1, 0, n-1);
  }
  pair<ll, int> get(int l, int r) {
    x = l, y = r, res = {-inf, 0};
    get(1, 0, n-1);
    return res;
  }
  pair<ll, int> get(int l) {
    return get(l, l);
  }
} dep;
struct HLD {
  int n, x, y;
  ll v, res;
  vector<ll> st, lz;
  HLD() {}
  HLD(int n): n(n), st(n * 2), lz(n * 2) { build(1, 0, n-1); }
  void build(int k, int l, int r) {
    if (l == r) 
      return st[k] = lpath[l], void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    build(lc, l, m), build(rc, m+1, r);
    st[k] = max(st[lc], st[rc]);
  }
  void push(int k, int lc, int rc) {
    ll w = lz[k]; lz[k] = 0;
    st[lc] += w, lz[lc] += w,
    st[rc] += w, lz[rc] += w;
  }
  void update(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return st[k] += v, lz[k] += v, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    update(lc, l, m), update(rc, m+1, r);
    st[k] = max(st[lc], st[rc]);
  }
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return res = max(res, st[k]), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    get(lc, l, m), get(rc, m+1, r);
  }
  void set(int k, int l, int r) {
    if (l > x || r < x) return;
    if (l == r) 
      return st[k] = v, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    set(lc, l, m), set(rc, m+1, r);
    st[k] = max(st[lc], st[rc]);
  }
  void add(int l, int r, ll w) {
    x = l, y = r, v = w;
    update(1, 0, n-1);
  }
  void set(int i, ll w) {
    x = i, v = w;
    set(1, 0, n-1);
  }
  ll get(int l, int r) {
    x = l, y = r, res = -inf;
    get(1, 0, n-1);
    return res;
  }
} hld;
vector<Edge> e;
vector<int> adj[N];
int siz[N], par[N], in[N], out[N], nxt[N];
void dfs0(int u = 1, int p = 0) {
  siz[u] = 1, par[u] = p;
  for (int& i : adj[u]) {
    int v = e[i].adj(u);
    if (v == p) continue;
    dfs0(v, u);
    siz[u] += siz[v];
    if (p == e[adj[u][0]].adj(u) || siz[v] > siz[e[adj[u][0]].adj(u)])
      swap(i, adj[u][0]);
  }
} 
int t = 0;
void dfs1(int u = 1, int p = 0, ll d = 0) {
  in[u] = t++;
  depth[in[u]] = {d, u};
  par[u] = p;
  for (int i : adj[u]) {
    int v = e[i].adj(u);
    if (v == p) continue;
    nxt[v] = i == adj[u][0] ? nxt[u] : v;
    dfs1(v, u, d + e[i].w);
  }
  out[u] = t-1;
}
int n, q, W;
void update(int u, int v, int w) {
  if (dep.get(in[u]).first < dep.get(in[v]).first) swap(u, v);
  if (u == 1) swap(u, v);
  dep.add(in[u], out[u], w);
  hld.add(in[u], out[u], -w);
  for (u = par[nxt[u]]; u; u = par[nxt[u]])
    hld.set(in[u], dep.get(out[e[adj[u][0]].adj(u)] + 1, out[u]).first - 2 * dep.get(in[u]).first);
}
ll diameter() {
  auto head = dep.st[1];
  ll res = head.first;  
  for (int u = head.second; u; u = par[nxt[u]]) {
    if (u != nxt[u]) 
      res = max(res, head.first + hld.get(in[nxt[par[u]]], in[par[u]]));
    res = max(res, max(dep.get(in[par[nxt[u]]], in[nxt[u]] - 1).first,
                       dep.get(out[nxt[u]] + 1, out[par[nxt[u]]]).first)
                       + head.first
                       - 2 * dep.get(in[par[nxt[u]]]).first);
  }
  return res;
}
signed main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q >> W;
for (int i = 0, u, v, w; i < n-1; ++i)
    cin >> u >> v >> w,
    adj[u].emplace_back(i),
    adj[v].emplace_back(i),
    e.emplace_back(u, v, w);
  nxt[1] = 1, dfs0(), dfs1();
  dep = Depth(n);
  for (int u = 1; u <= n; ++u)
    if (adj[u].size() == 1) lpath[in[u]] = -2 * depth[in[u]].first;
    else lpath[in[u]] = dep.get(out[e[adj[u][0]].adj(u)] + 1, out[u]).first -2 * depth[in[u]].first;
  hld = HLD(n);
  ll last = 0;
  for (int i = 0, d, c; i < q; ++i) {
    cin >> d >> c;
    d = (d + last) % (n - 1);
    c = (c + last) % W;
    update(e[d].u, e[d].v, c - e[d].w), e[d].w = c;
    last = diameter();
    cout << last << '\n';
  }
	return 0;
}


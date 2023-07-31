#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1.5e5 + 5, M = 998244353;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
int dif(int x, int y) {
  x -= y; if (x < 0) x += M; return x;
}
int mul(ll x, ll y) {
  return x * y % M;
}
int pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

struct SegmentTree {
  int n, x, y, v, res;
  vector<int> st;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2) {}
  void update(int k, int l, int r) {
    if (l > x || r < x) return;
    if (l == r)
      return add(st[k], v), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    update(lc, l, m), update(rc, m+1, r);
    st[k] = st[lc]; add(st[k], st[rc]);
  }
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y)
      return add(res, st[k]), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    get(lc, l, m), get(rc, m+1, r);
  }
  void update(int i, int v) {
    x = i, this->v = v;
    update(1, 1, n);
  }
  int get(int l, int r) {
    if (l > r) return 0;
    x = l, y = r, res = 0;
    get(1, 1, n);
    return res;
  }
  
} st;

vector<int> adj[N];
int siz[N], par[N], nxt[N], in[N];
int n, q;
void build(int u = 1, int p = 0) {
  siz[u] = 1;
  for (int& v : adj[u]) if (v != p) {
    build(v, u);
    siz[u] += siz[v];
    if (adj[u][0] == p || siz[v] > siz[adj[u][0]]) 
      swap(v, adj[u][0]);
  }
}
int t = 1;
void hld(int u = 1, int p = 0) {
  par[u] = p, in[u] = t++;
  for (int v : adj[u]) if (v != p) {
    nxt[v] = v == adj[u][0] ? nxt[u] : v;
    hld(v, u);
  }
}
int sum = 0, inv_n;
int cnt[N], val[N];
void update(int u, int d) {
  add(cnt[u], d);
  add(sum, mul(d, siz[u]));
  add(val[u], mul(d, siz[u]));
  if (adj[u].size())
    st.update(in[u], dif(mul(d, n - siz[adj[u][0]]), mul(d, siz[u])));
}
int get(int u) {
  int res = sum; 
  add(res, dif(mul(cnt[u], n), val[u]));
  add(res, st.get(in[nxt[u]], in[par[u]]));
  u = nxt[u];
  for (; u != 0;) {
    int p = par[u];
    add(res, st.get(in[nxt[p]], in[par[p]]));
    add(res, dif(mul(cnt[p], n - siz[u]), val[p]));
    u = nxt[p];
  }
  return mul(res, inv_n);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q; inv_n = pw(n, M - 2);
  for (int i = 0, u, v; i < n-1; ++i)  
    cin >> u >> v, 
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  build(1), nxt[1] = 1, hld(1);
  st = SegmentTree(n);
  for (int i = 0, t, v, d; i < q; ++i) {
    cin >> t >> v;
    if (t == 1)
      cin >> d, update(v, d);
    else
      cout << get(v) << '\n';
  }
	return 0;
}


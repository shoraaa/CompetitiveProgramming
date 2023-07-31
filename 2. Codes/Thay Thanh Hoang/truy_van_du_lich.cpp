#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

const int N = 2e5 + 5;
vector<int> adj[N];
int par[N][20], dep[N];
void dfs(int u = 1, int p = 0) {
  dep[u] = dep[p] + 1;
  par[u][0] = p;
  for (int i = 1; i < 20; ++i) 
    par[u][i] = par[par[u][i - 1]][i - 1];
  for (int v : adj[u]) if (v != p) dfs(v, u);
}
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int i = 19; ~i; --i) 
    if (dep[par[u][i]] >= dep[v]) u = par[u][i];
  if (u == v) return u;
  for (int i = 19; ~i; --i) if (par[u][i] != par[v][i])
    u = par[u][i], v = par[v][i];
  return par[u][0];
}

int dis(int u, int v) {
  return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

int q;

struct BIT {
  int n;
  vector<int> node;
  vector<ll> bit;
  void pre_update(int i) {
    node.emplace_back(i);
  }
  void build() {
    sort(node.begin(), node.end());
    node.erase(unique(node.begin(), node.end()), node.end());
    bit.resize(node.size());
  }
  
  void update(int i, int v) {
    for (int z = lower_bound(node.begin(), node.end(), i) - node.begin() + 1; 
          z <= node.size(); z += z & -z) bit[z - 1] += v;
  }
  ll get(int i) {
    ll res = 0;
    for (int z = upper_bound(node.begin(), node.end(), i) - node.begin(); 
          z; z -= z & -z) res += bit[z - 1];
    return res;
  }
  ll get(int l, int r) {
    return get(r) - get(l - 1);
  }
} bit[N];

struct SegmentTree {
  int n, x, y, v, t;
  struct Node {
    int in, out, v_in, v_out; ll val;
    Node(int in = 0, int out = 0, int v_in = 0, int v_out = 0, ll val = 0)
     : in(in), out(out), v_in(v_in), v_out(v_out), val(val) {}
  };
  vector<Node> st; ll res;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2) {}
  void push(const Node& p, Node& c) {
    if (!p.v_in) return;
    if (!c.v_in) {
      c = p;
    } else {
      c.val = c.val + p.val - dis(c.v_out, p.v_in) + bit[c.v_out].get(c.out, p.in);
      c.out = p.out; c.v_out = p.v_out;
    }
  }
  void push_back(Node& c) {
    if (!c.v_in) {
      c.in = c.out = t; 
      c.v_in = c.v_out = v; 
      c.val = 0;
    } else {
      c.val = c.val - dis(c.v_out, v) + bit[c.v_out].get(c.out, t);
      c.out = t; c.v_out = v;
    }
  }
  void update(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) return push_back(st[k]), void();
    int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
    push(st[k], st[lc]), push(st[k], st[rc]); st[k].v_in = 0;
    update(lc, l, m), update(rc, m+1, r);
  }
  void get(int k, int l, int r) {
    if (l == r) return res = st[k].val + bit[st[k].v_out].get(st[k].out, t), void();
    int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
    push(st[k], st[lc]), push(st[k], st[rc]); st[k].v_in = 0;
    if (x <= m) get(lc, l, m);
    else get(rc, m+1, r);
  }
  void update(int l, int r, int u, int i) {
    x = l, y = r, v = u, t = i;
    update(1, 1, n);
  }
  ll get(int i, int j) {
    x = i, t = j;
    get(1, 1, n);
    return res;
  }
} st;

int n, m;

signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> q;
  st = SegmentTree(m);
  for (int i = 1, u; i <= m; ++i) 
    cin >> u, st.update(i, i, u, 1);
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, 
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  dep[0] = -1, dfs();
  
  vector<tuple<int, int, int, int>> queries;
  for (int i = 2, id, l, r, x, u; i <= q + 1; ++i) {
    char ch; cin >> ch;
    if (ch == 't') cin >> l >> r >> u, queries.emplace_back(0, l, r, u);
    else if (ch == 'e') cin >> u >> x, queries.emplace_back(1, u, x, -1), bit[u].pre_update(i);
    else cin >> id, queries.emplace_back(2, id, -1, -1);
  }
  
  for (int i = 1; i <= n; ++i) bit[i].build();

  for (int i = 2, t, id, l, r, x, u; i <= q + 1; ++i) {
    tie(t, l, r, u) = queries[i - 2];
    if (t == 0) {
      st.update(l, r, u, i);
    } else if (t == 1) {
      bit[l].update(i, r);
    } else {
      cout << st.get(l, i) << '\n';
    } 
  }
	return 0;
}


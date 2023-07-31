#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = 1e9;

const int N = 1e6 + 5;
vector<int> adj[N];

int par[N], in[N], out[N], vet[N], t = 0;
void dfs(int u) {
  in[u] = t++; vet[in[u]] = u;
  for (int v : adj[u]) {
    adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
    par[v] = u, dfs(v);
  }
  out[u] = t-1;
}
 
struct SegmentTree {
  int n, x, y; int res;
  vector<int> st;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2) { build(1, 0, n-1); }
  void build(int k, int l, int r) {
    if (l == r)   
      return st[k] = vet[l], void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    build(lc, l, m), build(rc, m+1, r);
    st[k] = min(st[lc], st[rc]);
  }
  void update(int k, int l, int r) {
    if (l == r)
      return st[k] = inf, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    if (x <= m) update(lc, l, m);
    else update(rc, m+1, r);
    st[k] = min(st[lc], st[rc]);
  }
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y)
      return res = min(res, st[k]), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    get(lc, l, m), get(rc, m+1, r);
  }
  void erase(int u) {
    x = in[u];
    update(1, 0, n-1);
  }
  int get(int u) {
    x = in[u], y = out[u], res = inf;
    get(1, 0, n-1);
    return res;
  }
  int get(int l, int r) {
    x = l, y = r, res = inf;
    get(1, 0, n-1);
    return res;
  }
} st;

int ancestor(int u, int v) {
  return in[u] <= in[v] && out[u] >= out[v];
}

#define fi first
#define se second
int n;
int col[N], ans[N], cur;

int direction(int u, int v) {
  if (u == v) return v;
  if (!ancestor(u, v)) return -1;
  int lo = 0, hi = adj[u].size() - 1, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (in[adj[u][mid]] <= in[v])
      ans = adj[u][mid], lo = mid + 1;
    else
      hi = mid - 1;
  }
  return ans;
}

void solve(int u) {
  vector<int> path;
  int head = st.get(u), tail = head; path.emplace_back(head);
  col[head] = ++cur; st.erase(head); 
  for (;;) {
    int nxt = direction(head, tail);
    if (ancestor(head, tail)) {
      int a = st.get(tail);
      int b = nxt == -1 ? inf : min(st.get(in[u], in[nxt] - 1), st.get(out[nxt] + 1, out[u]));
      if (a == inf && b == inf) break;
      if (a < b) {
        for (int v = a; v != tail; v = par[v]) 
          col[v] = cur, st.erase(v), path.emplace_back(v);
        tail = a; 
      } else {
        int lca = b;
        for (;; lca = par[lca]) {
          col[lca] = cur, st.erase(lca), path.emplace_back(lca);
          if (ancestor(lca, head)) break;
        }
        for (int v = par[head]; ancestor(lca, v); v = par[v]) {
          if (v == lca) break;
          col[v] = cur, st.erase(v), path.emplace_back(v);
        }
        head = b;
      }
    } else {
      int a = st.get(tail);
      int b = st.get(head);
      if (a == inf && b == inf) break;
      if (a < b) {
        for (int v = a; v != tail; v = par[v])
          col[v] = cur, st.erase(v), path.emplace_back(v);
        tail = a; 
      } else {
        for (int v = b; v != head; v = par[v])
          col[v] = cur, st.erase(v), path.emplace_back(v);
        head = b; 
      }
    }
  }
  for (int u : path) for (int v : adj[u]) 
    if (v != par[v] && !col[v]) solve(v);
  if (!col[u]) solve(u);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  dfs(0); cur = 0; st = SegmentTree(n);
  
  solve(0); int val = 0;
  for (int v = 0; v < n; ++v) {
    if (!ans[col[v]]) ans[col[v]] = ++val;
    cout << ans[col[v]] << ' ';
  }
	return 0;
}

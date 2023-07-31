#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct SegmentTree {
  int n, x, y, v;
  struct Node {
    ll val = 0, lazy = 0;
  };
  vector<Node> st;
  
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 4) {}
  
  void apply(int i, int v) {
    st[i].val += v;
    st[i].lazy += v;
  }
  
  void push(int i) {
    if (!st[i].lazy) return;
    ll x = st[i].lazy;
    st[i].lazy = 0;
    
    st[i * 2].val += x;
    st[i * 2].lazy += x;
    
    st[i * 2 + 1].val += x;
    st[i * 2 + 1].lazy += x;
    
  }
  
  void pull(int i) {
    st[i].val = max(st[i * 2].val, st[i * 2 + 1].val);
  }
  
  void update(int i, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) {
      apply(i, v);
      return;
    }
    push(i);
    int m = (l + r) / 2;
    update(i * 2, l, m);
    update(i * 2 + 1, m + 1, r);
    pull(i);
  }
  
  void add(int l, int r, int v) {
    x = l, y = r, this->v = v;
    update(1, 1, n);
  }
  
} st;

const int N = 2e5 + 5;
vector<int> adj[N];
vector<pair<int, int>> score[N];

int n, m;

int vis[N], siz[N];
int dfs_size(int u, int p) {
  siz[u] = 1;
  for (int v : adj[u]) if (v != p && !vis[v]) {
    dfs_size(v, u);
    siz[u] += siz[v];
  }
  return siz[u];
}
int dfs_find(int u, int p, int s) {
  for (int v : adj[u]) if (v != p && !vis[v]) {
    if (siz[v] * 2 >= s) return dfs_find(v, u, s);
  }
  return u;
}


int in[N], out[N], t;
void dfs_t(int u, int p) {
  in[u] = ++t;
  for (int v : adj[u]) if (v != p && !vis[v]) {
    dfs_t(v, u);
  }
  out[u] = t;
}

int cur[N], pre[N];

void dfs_erase(int u, int p) {
  pre[u] = 0;
  for (int v : adj[u]) if (v != p && !vis[v]) {
    dfs_erase(v, u);
  }
}


ll path_w, res = 0;
vector<pair<int, ll>> vec;

void dfs(int u, int p) {
  cur[u] = 1;
  for (auto& pi : score[u]) {
    int v, w; tie(v, w) = pi;
    if (cur[v]) {
      path_w += w;
    } else if (pre[v]) {
      st.add(in[v], out[v], +w);
    }
  }
  
  res = max(res, st.st[1].val + path_w);
  vec.emplace_back(u, path_w);
  
  for (int v : adj[u]) if (v != p && !vis[v]) {
    dfs(v, u);
  }
  
  for (auto& pi : score[u]) {
    int v, w; tie(v, w) = pi;
    if (cur[v]) {
      path_w -= w;
    } else if (pre[v]) {
      st.add(in[v], out[v], -w);
    }
  }
  cur[u] = 0;
  
  
}

void solve(int u) {
  int si = dfs_size(u, 0);
  u = dfs_find(u, 0, si);
  
  t = 0; 
  dfs_t(u, 0);
  
  path_w = 0;
  for (auto& pi : score[u]) {
    int v, w; tie(v, w) = pi;
    if (v == u) {
      path_w += w;
    }
  }
  
  st = SegmentTree(t);
  cur[u] = 1;
  for (int v : adj[u]) if (!vis[v]) {
    vec.clear();
    dfs(v, u);
    for (auto& p : vec) {
      int v; ll w; tie(v, w) = p;
      pre[v] = 1;
      st.add(in[v], in[v], +w);
    }
  }
  cur[u] = 0;
  
  dfs_erase(u, 0);
  
  vis[u] = 1;
  for (int v : adj[u]) if (!vis[v]) {
    solve(v);
  }
  
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("upgrade.inp", "r")) {
    freopen("upgrade.inp", "r", stdin);
    freopen("upgrade.out", "w", stdout);
  }
  
  cin >> n;
  for (int i = 1, u, v; i <= n - 1; ++i) {
    cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  cin >> m;
  for (int i = 1, u, v, w; i <= m; ++i) {
    cin >> u >> v >> w;
    score[u].emplace_back(v, w);
    if (u != v) {
      score[v].emplace_back(u, w);
    }
  }
  solve(1);
  cout << res;
	return 0;
}


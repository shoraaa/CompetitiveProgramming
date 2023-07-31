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
int n, m;

int in[N], out[N], dep[N], par[N], t;
void dfs(int u) {
  in[u] = ++t;
  for (int v : adj[u]) {
    dep[v] = dep[u] + 1;
    par[v] = u;
    adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
    dfs(v);
  }
  out[u] = t;
}

struct Seg {
  int l, r, y, w;
  Seg(int l, int r, int y, int w): l(l), r(r), y(y), w(w) {}
  
  bool operator < (const Seg& s) const {
    return y < s.y;
  }
};
vector<Seg> seg;

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
  
  t = 0; 
  dfs(1);
  
  cin >> m;
  for (int i = 1, u, v, w; i <= m; ++i) {
    cin >> u >> v >> w;
    // in[u] <= in[x] <= out[u]
    // in[v] <= in[y] <= out[v]
    // => HCN (in[u], in[v]), (out[u], out[v]);
    // diem (in[x], in[y])
    if (dep[u] > dep[v]) swap(u, v);
    
    if (in[u] <= in[v] && in[v] <= out[u]) {
      // u la to tien v
      
      int i = lower_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
        return out[x] < out[y];
      }) - adj[u].begin();
      
      int p = adj[u][i];
      
      // in[1] -> in[p] - 1
      if (in[1] <= in[p] - 1) {
        seg.emplace_back(in[v], out[v], in[1], w);
        seg.emplace_back(in[v], out[v], in[p], -w);
        
        seg.emplace_back(in[1], in[p] - 1, in[v], w);
        seg.emplace_back(in[1], in[p] - 1, out[v] + 1, -w);
      }
      
      // out[p] + 1 -> out[1]
      if (out[p] + 1 <= out[1]) {
        seg.emplace_back(in[v], out[v], out[p] + 1, w);
        seg.emplace_back(in[v], out[v], out[1] + 1, -w);
           
        seg.emplace_back(out[p] + 1, out[1], in[v], w);
        seg.emplace_back(out[p] + 1, out[1], out[v] + 1, -w);
      }

    } else {
      seg.emplace_back(in[u], out[u], in[v], w);
      seg.emplace_back(in[u], out[u], out[v] + 1, -w);
      
      swap(u, v);
      
      seg.emplace_back(in[u], out[u], in[v], w);
      seg.emplace_back(in[u], out[u], out[v] + 1, -w);
      
    }

    
  }

  sort(seg.begin(), seg.end());
  
  ll res = 0;
  st = SegmentTree(n);
  
  for (int i = 0; i < seg.size();) {
    int j = i;
    while (j < seg.size() && seg[j].y == seg[i].y) {
      st.add(seg[j].l, seg[j].r, seg[j].w);
      j++;
    }
    
    res = max(res, st.st[1].val);
    i = j;
    
  }
  
  cout << res;
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5;

#define fi first
#define se second

struct SegmentTree {
  int n, x, y, v;
  vector<pair<int, int>> st;
  pair<int, int> res;
  SegmentTree(int n = 0): n(n), st(n * 4) {}
  
  void apply(int i, int v, int id) {
    st[i] = make_pair(v, id);
  }
  
  void pull(int i) {
    st[i] = max(st[i * 2], st[i * 2 + 1]);
  }
  
  void update(int i, int l, int r) {
    if (l == r) {
      apply(i, v, l);
      return;
    }
    int m = (l + r) / 2;
    if (x <= m) update(i * 2, l, m);
    else update(i * 2 + 1, m + 1, r);
    pull(i);
  }
  
  void get(int i, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) {
      res = max(res, st[i]);
      return;
    }
    int m = (l + r) / 2;
    get(i * 2, l, m);
    get(i * 2 + 1, m + 1, r);
  }
  
  void update(int i, int v) {
    x = i;
    this->v = v;
    update(1, 1, n);
  }
  
  pair<int, int> get(int l, int r) {
    x = l; y = r;
    res = make_pair(0, 0);
    get(1, 1, n);
    return res;
  }
  
} st;

struct Edge {
  int u, v, del = 0;
} ed[N];

struct Query {
  int t, i;
} qr[N];

int a[N];

int n, m, q;

vector<int> adj[N];
int lin[N];

int find(int u) {
  if (u == lin[u]) {
    return u;
  }
  return lin[u] = find(lin[u]);
}

void unite(int u, int v) {
  u = find(u); v = find(v);
  if (u == v) {
    return;
  }
  n++;
  lin[u] = lin[v] = lin[n] = n;
  adj[n].emplace_back(u);
  adj[n].emplace_back(v);
}

int in[N], out[N], t = 0;
void dfs(int u) {
  in[u] = ++t;
  st.update(in[u], a[u]);
  
  for (int v : adj[u]) {
    dfs(v);
  }
  out[u] = t;
}

int ans[N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  
  for (int i = 1; i <= m; ++i) {
    cin >> ed[i].u >> ed[i].v;
  }
  
  for (int i = 1; i <= q; ++i) {
    cin >> qr[i].t >> qr[i].i;
    if (qr[i].t == 2) {
      ed[qr[i].i].del = 1;
    }
  }
  
  for (int i = 1; i <= n; ++i) {
    lin[i] = i;
  }
  
  for (int i = 1; i <= m; ++i) {
    if (ed[i].del) continue;
    unite(ed[i].u, ed[i].v);
  }
  
  for (int i = q; i; --i) {
    if (qr[i].t == 1) {
      ans[i] = find(qr[i].i);
    } else if (ed[qr[i].i].del) {
      unite(ed[qr[i].i].u, ed[qr[i].i].v);
    }
  }
  
  st = SegmentTree(n);
  for (int i = 1; i <= n; ++i) {
    if (lin[i] == i) {
      dfs(i);
    }
  }
  
  for (int i = 1; i <= q; ++i) {
    if (qr[i].t == 2) continue;
    int p = ans[i];
    auto pi = st.get(in[p], out[p]);
    cout << pi.fi << '\n';
    st.update(pi.se, 0);
  }
  
	return 0;
}


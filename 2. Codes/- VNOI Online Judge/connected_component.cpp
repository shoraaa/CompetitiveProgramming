#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int ans[N];

#define fi first
#define se second

int lin[N], siz[N];

int find(int i) {
  if (i == lin[i]) return i;
  return find(lin[i]);
}

vector<pair<int, int>> st;
int unite(int u, int v) {
  u = find(u), v = find(v);
  if (u == v) return 0;
  if (siz[u] < siz[v]) swap(u, v);
  lin[v] = u, siz[u] += siz[v];
  st.emplace_back(u, v);
  return 1;
}

struct QueryTree {
  int n, x, y, u, v;
  vector<vector<pair<int, int>>> edges;
  vector<pair<int, int>> queries;
  QueryTree() = default;
  QueryTree(int n): n(n), edges(n * 4), queries(n + 1) {}
  
  void dfs(int i, int l, int r) {
    int m = (l + r) / 2;
    int cnt = 0;
    for (auto& p : edges[i]) {
      int u, v; tie(u, v) = p;
      cnt += unite(u, v);
    }
    
    if (l == r) {
      if (queries[l].fi) {
        int u, v; tie(u, v) = queries[l];
        ans[l] = find(u) == find(v);
      }
    } else {
      dfs(i * 2, l, m);
      dfs(i * 2 + 1, m + 1, r);
    }
    
    while (cnt--) {
      int u, v; tie(u, v) = st.back();
      st.pop_back();
      lin[v] = v, siz[u] -= siz[v];
    }
  }
  
  void update(int i, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return edges[i].emplace_back(u, v), void();
    int m = (l + r) / 2;
    update(i * 2, l, m);
    update(i * 2 + 1, m + 1, r);
  }
  
  void add(int l, int r, int u, int v) {
    x = l, y = r;
    this->u = u, this->v = v;
    update(1, 1, n);
  }
  
  void query(int i, int u, int v) {
    queries[i] = make_pair(u, v);
  }
  
} qt;

int n, q;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q;
  qt = QueryTree(q);
  map<pair<int, int>, vector<int>> edges;
  memset(ans, -1, sizeof(ans));
  for (int i = 1, t, u, v; i <= q; ++i) {
    cin >> t >> u >> v;
    if (u > v) swap(u, v);
    if (t == 1) {
      edges[{u, v}].emplace_back(i);
    } else if (t == 2) {
      if (edges[{u, v}].empty()) continue;
      int j = edges[{u, v}].back(); 
      edges[{u, v}].pop_back();
      qt.add(j, i, u, v);
    } else if (t == 3) {
      qt.query(i, u, v);
    }
  }
  for (auto& p : edges) {
    int u, v; tie(u, v) = p.fi;
    while (!p.se.empty()) {
      qt.add(p.se.back(), q, u, v);
      p.se.pop_back();
    }
  }
  for (int i = 1; i <= n; ++i)   
    lin[i] = i, siz[i] = 1;
  qt.dfs(1, 1, q);
  for (int i = 1; i <= q; ++i) if (ans[i] != -1)
    cout << ans[i];
	return 0;
}

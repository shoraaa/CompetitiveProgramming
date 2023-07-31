#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e4 + 5;
const int INF = 2e9 + 9;

struct Edge {
  int u, v, w;
  Edge(int u, int v, int w): u(u), v(v), w(w) {}
  
  bool operator < (const Edge& e) const {
    return w < e.w;
  }
  
};

vector<Edge> edges_a, edges_b;
int n, m, s, t;

int lin[N], siz[N];
int find(int i) {
  if (i == lin[i]) {
    return i;
  }
  return find(lin[i]);
}

stack<pair<int, int>> st;

int unite(int u, int v) {
  u = find(u), v = find(v);
  if (u == v) return 0;
  
  if (siz[u] < siz[v]) {
    swap(u, v);
  }
  
  lin[v] = u; 
  siz[u] += siz[v];
  
  st.emplace(u, v);
  
  return 1;
  
}

void rollback() {
  assert(!st.empty());
  
  int u, v; 
  tie(u, v) = st.top();
  st.pop();
  
  lin[v] = v;
  siz[u] -= siz[v];
  
}

int res = INF;

void solve(int l, int r, int x, int y) {
  if (l > r) return;
  
  // [x, y]
  
  int m1 = (l + r) / 2, m2 = -1;
  
  int added_a = 0, added_b = 0;
  
  for (int i = l; i <= m1; ++i) {
    auto e = edges_a[i];
    added_a += unite(e.u, e.v);
  }

  for (int i = x; i <= y; ++i) {
    auto e = edges_b[i];
    added_b += unite(e.u, e.v);
    
    if (find(s) == find(t)) {
      m2 = i;
      break;
    }
  }

  while (added_b > 0) { 
    rollback();
    added_b--;
  }
  
  solve(m1 + 1, r, x, m2 == -1 ? y : m2);
  
  while (added_a > 0) {
    rollback();
    added_a--;
  }
  
  if (m2 == -1) return;
  
  res = min(res, edges_a[m1].w + edges_b[m2].w);
  
  for (int i = x; i < m2; ++i) {
    auto e = edges_b[i];
    added_b += unite(e.u, e.v);
  }
  
  solve(l, m1 - 1, m2, y);
  
  while (added_b > 0) {
    rollback();
    added_b--;
  }
  
  
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> s >> t;
  
  edges_a.emplace_back(0, 0, 0);
  edges_b.emplace_back(0, 0, 0);
  
  for (int i = 1, u, v, w, c; i <= m; ++i) {
    cin >> c >> u >> v >> w;
    if (c == 1) {
      edges_a.emplace_back(u, v, w);
    } else {
      edges_b.emplace_back(u, v, w);
    }
  }
  
  sort(edges_a.begin(), edges_a.end());
  sort(edges_b.begin(), edges_b.end());
  
  for (int i = 0; i <= n; ++i) {
    lin[i] = i;
    siz[i] = 1;
  }
  
  solve(0, edges_a.size() - 1, 0, edges_b.size() - 1);
  
  cout << res;
  
	return 0;
}


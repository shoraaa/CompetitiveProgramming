#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
struct Edge {
  int u, v, w, t;
  Edge(int u, int v, int w, int t): u(u), v(v), w(w), t(t) {}
  bool operator < (const Edge& e) const {
    return w < e.w;
  }
};

struct DSU {
  int n, cnt; 
  int lin[N], siz[N];
  DSU(int n): n(n) {
    cnt = n;
    for (int i = 0; i < n; ++i) 
      lin[i] = i, siz[i] = 1;
  }
  int find(int u) {
    if (u == lin[u]) return u;
    return lin[u] = find(lin[u]);
  }
  int unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return 0;
    if (siz[u] < siz[v]) swap(u, v);
    lin[v] = u, siz[u] += siz[v], cnt--; return 1;
  }
};

int n1, n2, m1, m2;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n1 >> m1; vector<Edge> edges; edges.reserve(m1 + m2);
  for (int i = 0, u, v, w; i < m1; ++i)
    cin >> u >> v >> w, u--, v--,
    edges.emplace_back(u, v, w, 0);
  cin >> n2 >> m2;
  for (int i = 0, u, v, w; i < m2; ++i)
    cin >> u >> v >> w, u--, v--,
    edges.emplace_back(u, v, w, 1);
  sort(edges.begin(), edges.end());
  DSU hang(n1), cot(n2);
  ll res = 0;
  for (auto& e : edges) {
    if (e.t == 0) {
      // hang u va hang v
      if (hang.unite(e.u, e.v))   
        res += 1LL * cot.cnt * e.w;
    } else {
      // cot u va cot v
      if (cot.unite(e.u, e.v))
        res += 1LL * hang.cnt * e.w;
    }
  }
  cout << res;
	return 0;
}


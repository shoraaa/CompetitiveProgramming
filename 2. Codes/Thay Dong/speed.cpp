#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 5, M = 1e4 + 5, S = 100, inf = 1e9 + 5;
struct Edge {
  int u, v, w;
  Edge(int u, int v, int w): u(u), v(v), w(w) {}
};
vector<Edge> edges, cedges[M];
int c[M], bound[M];
int n, m, k;

int cc; stack<pair<int, int>> st;
int lin[N], siz[N];
int find(int u) {
  if (u == lin[u]) return u;
  return lin[u] = find(lin[u]);
}
void unite(int u, int v) {
  u = find(u), v = find(v);
  if (u == v) return;
  if (siz[u] < siz[v]) swap(u, v);
  st.emplace(u, v); cc--;
  lin[v] = u, siz[u] += siz[v];
}
void unite(int w) {
  for (auto& e : cedges[w])
    unite(e.u, e.v);
}
int ans[M];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    edges.emplace_back(u, v, w), c[i] = w;
  sort(c, c + m); k = unique(c, c + m) - c;
  for (auto& e : edges) {
    int nw = lower_bound(c, c + k, e.w) - c;
    cedges[nw].emplace_back(e);
  }
  pair<int, int> res = {inf, inf};
  for (int i = 0; i < k; ++i) {
    for (int i = 0; i < n; ++i) 
      lin[i] = i, siz[i] = 1;
    cc = n;
    for (int j = i; j < k; ++j) {
      unite(j);
      if (cc == 1) {
        res = min(res, pair<int, int>(c[j] - c[i], c[i]));
        break;
      }
    }
  }
  cout << res.second << ' ' << res.first + res.second << '\n';
	return 0;
	
}

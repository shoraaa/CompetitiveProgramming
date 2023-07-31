#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct Edge {
  int u, v, w;
  Edge(int u, int v, int w): u(u), v(v), w(w) {}
};
struct Query {
  int u, v, k;
  Query(int u, int v, int k): u(u), v(v), k(k) {}
};
const int N = 1e5 + 5;
vector<Edge> edges;
vector<Query> que;
vector<pair<int, int>> val[N];
vector<int> check[N];
int lo[N], hi[N], ans[N], t[N];
int n, m, q;

int li[N]; 
set<int> st[N];
void clear() {
  for (int u = 0; u < n; ++u)
    li[u] = u, st[u] = set<int>(), st[u].insert(t[u]);
}
int find(int u) {
  if (u == li[u]) return u;
  return li[u] = find(li[u]);
}
void unite(int u, int v) {
  u = find(u), v = find(v);
  if (u == v) return;
  if (st[u].size() < st[v].size()) swap(u, v);
  li[v] = u; for (int c : st[v]) st[u].insert(c);
}

int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> q;
  for (int u = 0; u < n; ++u)
    cin >> t[u];
  vector<int> cw; cw.reserve(m);
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--, 
    edges.emplace_back(u, v, w),
    cw.emplace_back(w);
  sort(cw.begin(), cw.end());
  cw.erase(unique(cw.begin(), cw.end()), cw.end());
  
  for (int i = 0; i < m; ++i) {
    auto e = edges[i]; 
    int id = lower_bound(cw.begin(), cw.end(), e.w) - cw.begin();
    val[id].emplace_back(e.u, e.v);
  }
  for (int i = 0, u, v, k; i < q; ++i) 
    cin >> u >> v >> k, u--, v--,
    que.emplace_back(u, v, k),
    lo[i] = 0, hi[i] = cw.size() - 1, ans[i] = -1;
  for (;;) {
    int flag = 0;
    for (int i = 0; i < q; ++i)
      if (lo[i] <= hi[i]) check[lo[i] + hi[i] >> 1].emplace_back(i), flag = 1;
    if (!flag) break;
    clear();
    for (int w = 0; w < cw.size(); ++w) {
      for (auto& p : val[w]) unite(p.first, p.second);
      while (!check[w].empty()) {
        int i = check[w].back(); check[w].pop_back();
        if (find(que[i].u) == find(que[i].v) && st[find(que[i].u)].size() >= que[i].k)
          ans[i] = w, hi[i] = w - 1;
        else
          lo[i] = w + 1;
      }
    }
  }
  for (int i = 0; i < q; ++i)
    cout << (ans[i] == -1 ? -1 : cw[ans[i]]) << '\n';
	return 0;
}


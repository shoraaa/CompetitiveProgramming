#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = 2e9, K = 30;
struct Node {
  int nxt[2], siz, idx, leaf;
  Node(): siz(0), idx(-1) {
    memset(nxt, 0, sizeof(nxt));
  }
};
struct Edge {
  int u, v, w;
  Edge(): w(inf) {}
  Edge(int u, int v, int w): u(u), v(v), w(w) {}
  bool operator < (const Edge& e) const {
    return w < e.w;
  }
};
vector<Node> pt;
#define bit(_msk, _i) ((_msk) >> (_i) & 1)
#define nxt(u, c) pt[u].nxt[c]
#define siz(u) pt[u].siz
#define idx(u) pt[u].idx
void add(int x, int id) {
  int u = 0;
  for (int i = K; ~i; --i) {
    if (!nxt(u, bit(x, i))) 
      nxt(u, bit(x, i)) = pt.size(),
      pt.emplace_back();
    u = nxt(u, bit(x, i));
    siz(u)++;
  }
  idx(u) = id;
}
void erase(int x) {
  int u = 0; 
  for (int i = K; ~i; --i) {
    u = nxt(u, bit(x, i));
    siz(u)--;
  }
}
vector<int> _c[2];
int best(int x) {
  int u = 0;
  for (int i = K; ~i; --i) {
    for (int c : _c[bit(x, i)]) if (siz(nxt(u, c))) {
      u = nxt(u, c); break;
    }
  }
  return idx(u);
}
const int N = 2e5 + 5;
int li[N]; vector<int> comp[N];
int find(int u) {
  if (u == li[u]) return u;
  return li[u] = find(li[u]);
}
ll res = 0; int cnt = 0;
void unite(Edge e) {
  int u = e.u, v = e.v, w = e.w;
  u = find(u), v = find(v);
  if (u == v) return; res += w, cnt++;
  if (comp[u].size() < comp[v].size()) swap(u, v);
  li[v] = u; for (int c : comp[v]) comp[u].emplace_back(c); 
  vector<int>().swap(comp[v]); // o(n) memory
}
int a[N]; bool vis[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	_c[0] = {0, 1}, _c[1] = {1, 0};
  cin >> n; pt = vector<Node>(1);
  for (int i = 0; i < n; ++i) 
    cin >> a[i];
  sort(a, a + n); n = unique(a, a + n) - a;
  for (int i = 0; i < n; ++i)
    add(a[i], i);
  for (int u = 0; u < n; ++u)
    li[u] = u, comp[u].emplace_back(u);
  stack<Edge> edges;
  for (;;) {
    if (cnt == n-1) break;
    memset(vis, 0, sizeof(bool) * n);
    for (int u = 0; u < n; ++u) if (!vis[u]) {
      auto medge = Edge(); int root = find(u);
      for (int v : comp[root]) erase(a[v]);
      for (int v : comp[root]) {
        int e = best(a[v]); vis[v] = 1;
        medge = min(medge, Edge(v, e, a[v] ^ a[e]));
      }
      for (int v : comp[root]) add(a[v], v);
      if (medge.w != inf) edges.emplace(medge);
    }
    while (!edges.empty())
      unite(edges.top()),
      edges.pop();
  }
  cout << res;
	return 0;
}


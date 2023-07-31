#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
const ll inf = 1e18;
struct AdjacentEdge {
  int v, w;
  AdjacentEdge(int v, int w): v(v), w(w) {}
  bool operator < (const AdjacentEdge& c) const {
    return w < c.w;
  }
};
struct State {
  int u, i; ll d;
  State(int u, int i, ll d): u(u), i(i), d(d) {}
  bool operator < (const State& s) const {
    return d > s.d;
  }
};
vector<AdjacentEdge> adj[N];
int cur[N];
int n, m, d;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	if (fopen("danang.inp", "r")) 
    freopen("danang.inp", "r", stdin),
    freopen("danang.out", "w", stdout);
	cin >> n >> m >> d;
	for (int i = 0, u, v, w; i < m; ++i)
	  cin >> u >> v >> w, u--, v--,
	  adj[u].emplace_back(v, w),
	  adj[v].emplace_back(u, w);
  for (int u = 0; u < n; ++u)
    sort(adj[u].begin(), adj[u].end()), cur[u] = adj[u].size() - 1;
  priority_queue<State> q;
  for (int i = 0; i < adj[0].size(); ++i) 
    q.emplace(0, i, adj[0][i].w);
  cur[0] = -1;
  while (!q.empty()) {
    auto s = q.top(); q.pop(); 
    int u = s.u, i = s.i, v = adj[s.u][s.i].v;
    if (v == n-1) return cout << s.d, 0;
    while (~cur[v] && adj[u][i].w + d <= adj[v][cur[v]].w) 
      q.emplace(v, cur[v], s.d + adj[v][cur[v]].w), cur[v]--;
  }
  cout << -1;
	return 0;
}

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
int n, m, d;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m >> d;
	for (int i = 0, u, v, w; i < m; ++i)
	  cin >> u >> v >> w, u--, v--,
	  adj[u].emplace_back(v, w),
	  adj[v].emplace_back(u, w);
  for (int u = 0; u < n; ++u)
    sort(adj[u].begin(), adj[u].end());
  priority_queue<State> q;
  for (int i = 0; i < adj[0].size(); ++i) 
    q.emplace(0, i, adj[0][i].w);
  while (!q.empty()) {
    auto s = q.top(); q.pop(); 
    int u = s.u, i = s.i, v = adj[s.u][s.i].v;
    if (v == n-1) return cout << s.d, 0;
    while (!adj[v].empty() && adj[u][i].w + d <= adj[v].back().w) {
      q.emplace(v, adj[v].size() - 1, s.d + adj[v].back().w);
      adj[v].pop_back();
    }
  }
  cout << -1;
	return 0;
}

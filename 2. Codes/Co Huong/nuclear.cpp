#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct Adjacent {
  int v, w;
  Adjacent(int v, int w): v(v), w(w) {}
};
struct State {
  int u; ll d;
  State(int u, ll d): u(u), d(d) {}
  bool operator < (const State& s) const {
    return d > s.d;
  }
};
const int N = 1e5 + 5;
vector<Adjacent> adj[N];
ll dis[N];
int n, m, k, t;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("nuclear.in", "r"))
    freopen("nuclear.in", "r", stdin),
    freopen("nuclear.out", "w", stdout);
  cin >> n >> m;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    adj[u].emplace_back(v, w),
    adj[v].emplace_back(u, w);
  memset(dis, 0x3f, sizeof(dis));
  priority_queue<State> q;
  cin >> k;
  for (int i = 0, u; i < k; ++i)
    cin >> u, u--,
    dis[u] = 0, q.emplace(u, 0);
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    if (s.d != dis[s.u]) continue;
    for (auto& c : adj[s.u]) if (s.d + c.w < dis[c.v])
      dis[c.v] = s.d + c.w, 
      q.emplace(c.v, dis[c.v]);
  }
  cin >> t;
  for (int i = 0, u; i < t; ++i)
    cin >> u, u--,
    cout << dis[u] << ' ';
	return 0; 
}


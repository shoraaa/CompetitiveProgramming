#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "quanho";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
const ll llinf = 1e18;
struct C {
  int v, w;
  C(int v, int w): v(v), w(w) {}
};
struct S {
  int u; ll d;
  S(int u, ll d): u(u), d(d) {}
  bool operator < (const S& s) const {
    return d > s.d;
  }
};
vector<C> adj[N];
int p[N];
ll dis[N], dp[N];
int n, m;
ll call(int u) {
  if (dp[u] != -1)
    return dp[u];
  ll res = p[u];
  for (C& c : adj[u]) if (dis[c.v] + c.w == dis[u])
    res = max(res, call(c.v) + p[u]);
  return dp[u] = res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> p[i];
  cin >> m;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    adj[u].emplace_back(v, w),
    adj[v].emplace_back(u, w);
  priority_queue<S> q;
  q.emplace(0, 0);
  fill(begin(dis), end(dis), llinf);
  dis[0] = 0;
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    if (s.d != dis[s.u]) continue;
    for (C& c : adj[s.u]) if (s.d + c.w < dis[c.v])
      dis[c.v] = s.d + c.w,
      q.emplace(c.v, dis[c.v]);
  }
  if (dis[n-1] == llinf)
    return cout << "impossible", 0;
  fill(begin(dp), end(dp), -1);
  cout << dis[n-1] << ' ' << call(n-1);
	return 0;
}


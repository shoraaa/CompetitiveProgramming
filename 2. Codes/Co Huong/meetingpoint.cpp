#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "meetingpoint";
	if (!fopen((FILE_NAME + ".inp").c_str(), "r")) return;
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
struct AdjacentEdge {
  int v, w;
  AdjacentEdge(int v, int w): v(v), w(w) {}
};
struct State {
  int u; ll d;
  State(int u, ll d): u(u), d(d) {}
  bool operator < (const State& s) const {
    return d > s.d;
  }
};
const int N = 2e5 + 5;
vector<AdjacentEdge> adj[N];
ll a[N], b[N], f[N], g[N];
pair<ll, ll> p[N];
int n, m, k;
int check(ll c, ll x, ll y) {
  int lo = 0, hi = n-1, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (p[mid].first * x <= c)
      ans = mid, lo = mid + 1;
    else
      hi = mid - 1;
  }
  if (ans == -1) return 0;
  return p[ans].second * y <= c;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0); file();
  cin >> n >> m >> k;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    adj[u].emplace_back(v, w),
    adj[v].emplace_back(u, w);
  for (int i = 0; i < k; ++i)
    cin >> a[i] >> b[i];
  priority_queue<State> q;
  memset(f, 0x3f, sizeof(f));
  f[0] = 0; q.emplace(0, 0);
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    if (s.d != f[s.u]) continue;
    for (auto& c : adj[s.u]) if (s.d + c.w < f[c.v])
      f[c.v] = s.d + c.w, q.emplace(c.v, f[c.v]);
  }
  memset(g, 0x3f, sizeof(g));
  g[n-1] = 0; q.emplace(n-1, 0);
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    if (s.d != g[s.u]) continue;
    for (auto& c : adj[s.u]) if (s.d + c.w < g[c.v])
      g[c.v] = s.d + c.w, q.emplace(c.v, g[c.v]);
  }
  for (int i = 0; i < n; ++i) 
    p[i] = {f[i], g[i]};
  sort(p, p + n);
  for (int i = 1; i < n; ++i)
    p[i].second = min(p[i].second, p[i-1].second);
  for (int i = 0; i < k; ++i) {
    ll lo = 0, hi = 1e18, mid, ans;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (check(mid, a[i], b[i]))
        ans = mid, hi = mid - 1;
      else
        lo = mid + 1;
    }
    cout << ans << '\n';
  }
	return 0;
}


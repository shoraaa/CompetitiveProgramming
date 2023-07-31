#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
int a[N]; ll ans[N];
vector<int> adj[N];
struct Centroid {
  int siz[N], vis[N];
  int size(int u, int p = -1) {
    siz[u] = 1;
    for (int v : adj[u]) if (v != p && !vis[v])
      siz[u] += size(v, u);
    return siz[u];
  }
  int find(int u, int s, int p = -1) {
    for (int v : adj[u]) if (v != p && !vis[v] && siz[v] > s)
      return find(v, s, u);
    return u;
  }
  vector<int> vert;
  int delta[N], up_most[N], used[N];
  void dfs(int u, int p, int d, int c) {
    vert.emplace_back(u);
    up_most[u] = !used[a[u]];
    used[a[u]]++;
    d += up_most[u];
    ans[u] += d;
    if (u != c)
      ans[c] += d;
    for (int v : adj[u]) if (v != p && !vis[v])
      dfs(v, u, d, c);
    used[a[u]]--;
  }
  int path, sum;
  void update(int u, int p) {
    path++;
    if (up_most[u]) 
      sum += siz[u], delta[a[u]] += siz[u];
    for (int v : adj[u]) if (v != p && !vis[v])
      update(v, u);
  }
  void get(int u, int p, int d = 1) {
    if (up_most[u]) 
      sum -= delta[a[u]], d++;
    ans[u] += sum + ll(path) * d;
    for (int v : adj[u]) if (v != p && !vis[v])
      get(v, u, d);
    if (up_most[u])
      sum += delta[a[u]];
  }
  void solve(int u = 0) {
    u = find(u, size(u) / 2);
    size(u);
    vert.clear();
    dfs(u, -1, 0, u);
    for (int t = 0; t < 2; ++t) {
      sum = path = 0;
      for (int v : vert)
        delta[a[v]] = 0;
      for (int v : adj[u]) if (!vis[v])
        get(v, u),
        update(v, u);
      reverse(adj[u].begin(), adj[u].end());
    }
    vis[u] = 1;
    for (int v : adj[u]) if (!vis[v])
      solve(v);
  }
} ct;
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int u = 0; u < n; ++u)
    cin >> a[u];
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  ct.solve();
  for (int u = 0; u < n; ++u)
    cout << ans[u] << '\n';
	return 0;
}


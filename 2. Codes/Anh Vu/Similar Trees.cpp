#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 105;

struct Matching {
  vector<int> adj[N];
  int vis[N], match[N];
  void clear() {
    for (int i = 0; i < N; ++i) adj[i].clear();
  }
  void add(int u, int v) {
    adj[u].emplace_back(v);
  }
  int dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u]) if (!~match[v])
      return match[v] = u, 1;
    for (int v : adj[u]) if (!vis[match[v]] && dfs(match[v]))
      return match[v] = u, 1;
    return 0;
  }
  int get() {
    int res = 0;
    memset(match, -1, sizeof(match));
    for (int u = 0; u < N; ++u) if (adj[u].size()) {
      memset(vis, 0, sizeof(vis));
      res += dfs(u);
    }
    return res;
  }
} matching;

vector<int> g[N], t[N], d[N];
void dfs1(int u = 0, int dep = 0) {
  d[dep].emplace_back(u);
  for (int v : g[u]) {
    g[v].erase(find(g[v].begin(), g[v].end(), u));
    dfs1(v, dep + 1);
  }
}
void dfs2(int u = 0) {
  for (int v : t[u]) {
    t[v].erase(find(t[v].begin(), t[v].end(), u));
    dfs2(v);
  }
}
int dp[N][N];
void dfs(int u = 0, int dep = 0) {
  for (int v : t[u]) dfs(v, dep + 1);
  for (int v : d[dep]) {
    matching.clear();
    for (int x : t[u]) for (int y : g[v]) if (dp[x][y])
      matching.add(x, y);
    dp[u][v] = matching.get() == t[u].size();
  }
}
int n, m;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  for (int i = 1; i <= T; ++i) {
    cin >> n;
    for (int i = 0; i < n; ++i) g[i].clear(), d[i].clear();
    for (int i = 0, u, v; i < n-1; ++i)
      cin >> u >> v, u--, v--,
      g[u].emplace_back(v),
      g[v].emplace_back(u);
    cin >> m;
    for (int i = 0; i < m; ++i) t[i].clear(), d[i].clear();
    for (int i = 0, u, v; i < m-1; ++i)
      cin >> u >> v, u--, v--,
      t[u].emplace_back(v),
      t[v].emplace_back(u);
    dfs1(); dfs2();
    memset(dp, 0, sizeof(dp));
    dfs();
    cout << "Case " << i << (dp[0][0] ? ": Yes\n" : ": No\n");
  }    

	return 0;
}


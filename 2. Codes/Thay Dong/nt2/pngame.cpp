#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 505;
vector<int> adj[N], rev[N];

int vis[N], from[N], to[N];

int n1, n2, m;

int dfs(int u) {
  vis[u] = 1;
  for (int v : adj[u]) if (!~to[v])
    return to[v] = u, from[u] = v, 1;
  for (int v : adj[u]) if (!vis[to[v]] && dfs(to[v]))
    return to[v] = u, from[u] = v, 1;
  return 0;
}

int dfs1(int u) {
  vis[u] = 1;
  for (int v : adj[u]) if (!~to[v])
    return 1;
  for (int v : adj[u]) if (!vis[to[v]] && dfs1(to[v]))
    return 1;
  return 0;
}

int dfs2(int u) {
  vis[u] = 1;
  for (int v : rev[u]) if (!~from[v])
    return 1;
  for (int v : rev[u]) if (!vis[from[v]] && dfs2(from[v]))
    return 1;
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n1 >> n2 >> m;
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    rev[v].emplace_back(u);
  memset(to, -1, sizeof(to));
  memset(from, -1, sizeof(from));
  for (int i = 0; i < n1; ++i) {
    memset(vis, 0, sizeof(vis));
    dfs(i);
  }
  
  for (int i = 0; i < n1; ++i) {
    memset(vis, 0, sizeof(vis));
    cout << ((from[i] == -1 || dfs2(from[i])) ? 'P' : 'N'); 
  }
  cout << '\n';
  for (int i = 0; i < n2; ++i) {
    memset(vis, 0, sizeof(vis));
    cout << ((to[i] == -1 || dfs1(to[i])) ? 'P' : 'N'); 
  }
  
	return 0;
}

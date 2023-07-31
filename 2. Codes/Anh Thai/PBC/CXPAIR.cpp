#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
vector<int> adj[N];
int n, m;

int lin[N], siz[N];
int find(int u) {
  if (u == lin[u]) return u;
  return lin[u] = find(lin[u]);
}
void unite(int u, int v) {
  u = find(u), v = find(v);
  if (u == v) return;
  if (siz[u] < siz[v]) swap(u, v);
  lin[v] = u, siz[u] += siz[v];
}

int in[N], low[N], vis[N], t = 0;
vector<pair<int, int>> edges;
void dfs(int u, int p = -1) {
  vis[u] = 1;
  in[u] = low[u] = t++;
  for (int v : adj[u]) {
    if (v == p) continue;
    if (vis[v]) low[u] = min(low[u], in[v]);
    else {
      dfs(v, u), low[u] = min(low[u], low[v]);
      if (in[u] < low[v]) edges.emplace_back(u, v);
      else unite(u, v);  
    }
  }
}

vector<int> tree[N], comp[N];
int f[N];
ll res = 0;
void dfs1(int u, int p = -1) {
  vis[u] = 1; 
  for (int c : comp[u]) {
    int cur = 0, v;
    for (int to : tree[c]) if (!vis[v = find(to)]) {
      dfs1(v, to);
      res += f[v] - 1; // den u
      res += 1LL * f[v] * cur; 
      cur += f[v];
      
      if (siz[u] == 1 || c == p) f[u] += f[v];
    }
  }
  f[u]++;
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  for (int i = 0; i < n; ++i) lin[i] = i, siz[i] = 1;
  for (int i = 0; i < n; ++i) 
    if (!vis[i]) dfs(i);
  for (int i = 0; i < n; ++i) comp[find(i)].emplace_back(i);
  for (auto& e : edges) {
    int u, v; tie(u, v) = e;
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
  }
  for (int i = 0; i < n; ++i) vis[i] = 0;
  
  for (int i = 0; i < n; ++i) 
    if (!vis[find(i)]) dfs1(find(i));
  cout << res;
  
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;
vector<int> adj[N], tmp[N];
int n, m, cc = 1;
int comp[N];

void add_edge(int u, int v) {
  tmp[u].emplace_back(v + n),
  tmp[u + n].emplace_back(v),
  tmp[v].emplace_back(u + n),
  tmp[v + n].emplace_back(u);
}

int low[N], in[N], t = 0;
void dfs1(int u, int p = -1) {
  low[u] = in[u] = ++t;
  for (int v : adj[u]) {
    if (v == p) continue;
    if (in[v]) low[u] = min(low[u], in[v]), add_edge(u, v);
    else {
      dfs1(v, u);
      if (low[v] <= low[u]) add_edge(u, v);
      low[u] = min(low[u], low[v]);
    }
  }
}

void dfs2(int u) {
  comp[u] = cc; 
  for (int v : tmp[u]) 
    if (!comp[v]) dfs2(v);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, u, v; i < m; ++i) 
    cin >> u >> v, 
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  for (int u = 1; u <= n; ++u) 
    if (!in[u]) dfs1(u);
    
  for (int u = 1; u <= n * 2; ++u) 
    if (!comp[u]) dfs2(u), cc++;
    
  int res = 0;
  for (int u = 1; u <= n; ++u) {
    if (comp[u] == comp[u + n]) res++;
  }
  cout << res;
	return 0;
}


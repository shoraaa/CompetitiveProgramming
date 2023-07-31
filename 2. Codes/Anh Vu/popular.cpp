#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1.5e5 + 5, inf = 1e9;
vector<int> adj[N], scc[N], vert[N], rev[N];
int in[N], low[N], com[N];
int n, m, t = 0, cc = 0; 
stack<int> st;
void build(int u) {
  in[u] = low[u] = ++t;
  st.emplace(u);
  for (int v : adj[u]) 
    if (in[v]) low[u] = min(low[u], in[v]);
    else build(v), low[u] = min(low[u], low[v]);
  if (low[u] == in[u]) {
    int v;
    do {
      v = st.top(); st.pop();
      com[v] = cc, vert[cc].emplace_back(v);
      in[v] = low[v] = inf;
    } while (v != u);
    cc++;
  }
}
int deg[N], no[N];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v);
  for (int v = 0; v < n; ++v)
    if (!in[v]) build(v);
  for (int u = 0; u < n; ++u) for (int v : adj[u])
    if (com[u] != com[v]) scc[com[u]].emplace_back(com[v]);
  n = cc;
  for (int u = 0; u < n; ++u)
    sort(scc[u].begin(), scc[u].end()),
    scc[u].erase(unique(scc[u].begin(), scc[u].end()), scc[u].end());
  for (int u = 0; u < n; ++u) 
    for (int v : scc[u]) deg[v]++, rev[v].emplace_back(u);
  queue<int> q; 
  for (int v = 0; v < n; ++v)
    if (!deg[v]) q.emplace(v);
  vector<int> ans, topo; t = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    topo.emplace_back(u); in[u] = t++;
    for (int v : scc[u]) {
      deg[v]--;
      if (deg[v] == 0) {
        q.emplace(v);
      }
    }
  }
  int cur = -1;
  for (int u : topo) {
    if (cur > in[u]) no[u] = 1;
    int val = n+1;
    for (int v : scc[u]) 
      val = min(val, in[v]);
    cur = max(cur, val);
  }
  reverse(topo.begin(), topo.end());
  cur = n+1;
  for (int u : topo) {
    if (cur < in[u]) no[u] = 1;
    int val = -1;
    for (int v : rev[u]) 
      val = max(val, in[v]);
    cur = min(cur, val);
  }
  for (int u = 0; u < n; ++u) if (!no[u]) 
    for (int v : vert[u]) ans.emplace_back(v);
  sort(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (int v : ans)
    cout << v+1 << ' ';
	return 0;
}


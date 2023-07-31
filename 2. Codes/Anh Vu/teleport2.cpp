#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int nxt[N][30], out[N], siz[N], in[N], dep[N], idx[N];
vector<int> adj[N];
int n, m, id = 0;
void dfs(int u, int size = 1) {
  int v = nxt[u][0];
  if (!idx[v]) {
    idx[v] = idx[u];
    dep[v] = dep[u] + 1;
    dfs(v, size + 1); 
    siz[u] = siz[v];
  } else siz[u] = size;
}
void build(int u) {
  for (int v : adj[u]) {
    idx[v] = idx[u];
    dep[v] = dep[u] + 1;
    build(v);
  }
}
int solve(int u, int v) {
  if (u == v) return 0;
  int cnt = 0;
  if (out[v]) {
    if (!out[u] || idx[u] != idx[v] || dep[u] < dep[v]) 
      return -1;
    for (int i = 29; ~i; --i)
      if (out[nxt[u][i]] && dep[nxt[u][i]] > dep[v]) cnt += 1 << i, u = nxt[u][i];
    return nxt[u][0] == v ? cnt + 1 : -1;
  } else {
    if (out[u]) {
      for (int i = 29; ~i; --i)
        if (out[nxt[u][i]]) cnt += 1 << i, u = nxt[u][i];
      u = nxt[u][0], cnt++;
    }
    if (idx[u] != idx[v]) 
      return -1;
    cnt += (dep[v] - dep[u] + siz[u]) % siz[u];
    return cnt;
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> nxt[i][0], in[nxt[i][0]]++,
    adj[nxt[i][0]].emplace_back(i);
  for (int k = 1; k < 30; ++k)
    for (int i = 1; i <= n; ++i)
      nxt[i][k] = nxt[nxt[i][k-1]][k-1];
  queue<int> q;
  for (int i = 1; i <= n; ++i)
    if (!in[i]) q.emplace(i);
  vector<int> roots;
  while (!q.empty()) {
    int u = q.front(), v = nxt[u][0]; q.pop(); 
    out[u] = 1; in[v]--;
    if (!in[v]) q.emplace(v);
    else roots.emplace_back(u);
  }
  
  for (int u : roots) 
    idx[u] = ++id, build(u);
  for (int u = 1; u <= n; ++u) if (!out[u] && !idx[u])
    idx[u] = ++id, dfs(u);
  
  for (int i = 0, u, v; i < m; ++i) 
    cin >> u >> v,
    cout << solve(u, v) << '\n';
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
vector<pair<int, int>> adj[N], tree[N];
vector<int> bridge;
pair<int, int> edges[N];
int n, m, q;

vector<int> st;
int in[N], low[N], idx[N], id = 0, t = 0;
void dfs(int u, int pe = -1) {
  in[u] = low[u] = ++t;
  st.emplace_back(u);
  for (auto& p : adj[u]) {
    int v, e; tie(v, e) = p;
    if (idx[v] || e == pe) continue;
    if (!in[v]) {
      dfs(v, e);
      low[u] = min(low[u], low[v]);
      if (low[v] > in[u]) bridge.emplace_back(e);
    } else {
      low[u] = min(low[u], in[v]);
    }  
  }
  if (low[u] == in[u]) {
    idx[u] = ++id;
    while (!st.empty()) {
      int v = st.back(); st.pop_back();
      idx[v] = idx[u];
      if (v == u) break;
    }
  }
}

int dep[N], par[N][20];
void dfs2(int u, int p = 0) {
  dep[u] = dep[p] + 1;
  par[u][0] = p;
  for (int i = 1; i < 20; ++i)
    par[u][i] = par[par[u][i - 1]][i - 1];
  
  for (auto& pi : tree[u]) {
    int v, e; tie(v, e) = pi;
    if (v == p) continue;
    dfs2(v, u);
  }
}

int lca(int u, int v) {
  if (dep[u] <= dep[v]) swap(u, v);
  for (int i = 19; ~i; --i) if (dep[par[u][i]] >= dep[v]) u = par[u][i];
  if (u == v) return u;
  for (int i = 19; ~i; --i) if (par[u][i] != par[v][i])
    u = par[u][i], v = par[v][i];
  return par[u][0];
}

int dir[N][20];
int ans[N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, u, v; i < m; ++i) {
    cin >> u >> v;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
    edges[i] = {u, v};
  }
  for (int i = 1; i <= n; ++i)
    if (!in[i]) dfs(i);
  for (auto& i : bridge) {
    int u, v; tie(u, v) = edges[i];
    u = idx[u], v = idx[v];
    tree[u].emplace_back(v, i);
    tree[v].emplace_back(u, i);
  }
  for (int i = 1; i <= n; ++i) {
    sort(tree[i].begin(), tree[i].end());
    tree[i].erase(unique(tree[i].begin(), tree[i].end()), tree[i].end());
  }
  
  dep[0] = -1;
  for (int i = 1; i <= id; ++i) 
    if (!par[i][0]) dfs2(i);

  cin >> q;
  for (int i = 0, u, v; i < q; ++i) {
    cin >> u >> v; 
    u = idx[u]; v = idx[v];
    int z = lca(u, v);
    for (int i = 19; ~i; --i) {
      if (dep[par[u][i]] >= dep[z])
        dir[u][i] = 1, u = par[u][i];
      if (dep[par[v][i]] >= dep[z])
        dir[v][i] = 2, v = par[v][i];
     }
  }
  
  for (int i = 19; ~i; --i)  {
    for (int u = 1; u <= id; ++u) if (dir[u][i]) {
      dir[u][i - 1] = dir[u][i];
      dir[par[u][i - 1]][i - 1] = dir[u][i];
    }
  }
  
  for (auto& i : bridge) {
    int u, v; tie(u, v) = edges[i];
    u = idx[u], v = idx[v];
    if (dep[u] > dep[v]) {
      ans[i] = dir[u][0];
    } else {
      if (dir[v][0] == 0) continue;
      ans[i] = 3 - dir[v][0];
    }
  }
  
  for (int i = 0; i < m; ++i) {
    if (!ans[i]) cout << 'B';
    else if (ans[i] == 1) cout << 'R';
    else cout << 'L';
  }
  
	return 0;
}


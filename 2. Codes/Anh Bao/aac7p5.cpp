#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define fi first
#define se second

const int N = 5e5 + 5;
vector<int> adj[N];
pair<int, int> f[N];
int dep[N], dm[N], mn[N], ma[N];
int n;

void dfs1(int u, int p = 0) {
  dep[u] = dep[p] + 1;
  f[u] = {-1, u};
  for (int v : adj[u]) if (v != p) {
    dfs1(v, u);
    f[u] = max(f[u], f[v]);
  }
  f[u].fi++;
}


void dfs2(int u) {
  f[u] = {-1, u};
  dm[u] = -1; 
  mn[u] = u;
  for (int v : adj[u]) {
    adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
    dfs2(v);
    mn[u] = min(mn[u], mn[v]);
    f[u] = max(f[u], f[v]);
  }
  
  for (int v : adj[u]) {
    if (f[v].fi == f[u].fi) {
      if (dm[u] == -1 || mn[v] > mn[dm[u]]) {
        dm[u] = v;
      }
    }
  }
  
  f[u].fi++;
}

vector<int> res;

void dfs(int u, bool on_path) {
  
  if (adj[u].empty()) {
    res.emplace_back(u);
    return;
  }
  
  if (on_path) {
    adj[u].erase(find(adj[u].begin(), adj[u].end(), dm[u]));
  }
  
  sort(adj[u].begin(), adj[u].end(), [&](int i, int j) {
    return mn[i] < mn[j];
  });
  
  int pushed_u = 0;
  for (int v : adj[u]) {
    if (!pushed_u && u < mn[v]) {
      res.emplace_back(u);
      pushed_u = 1;
    }
    dfs(v, 0);
  }
  
  
  if (!pushed_u) res.emplace_back(u);
  
  if (on_path) {
    dfs(dm[u], 1);
  }
  
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0, u, v; i < n - 1; ++i) {
    cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  dep[0] = -1;
  
  dfs1(1);
  
  int s = f[1].se;
  dfs1(s);
  
  int r = s;
  
  for (int i = 1; i <= n; ++i) if (dep[i] == f[s].fi) {
    r = min(r, i);
  }
  
  s = f[s].se; 
  dfs1(s);
  
  for (int i = 1; i <= n; ++i) if (dep[i] == f[s].fi) {
    r = min(r, i);
  }
  
  dfs2(r);
  
  dfs(r, 1);
  
  for (int u : res) {
    cout << u;
    if (u != res.back()) cout << ' ';
    else cout << '\n';
  }
  
	return 0;
}


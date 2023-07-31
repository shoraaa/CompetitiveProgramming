#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
vector<int> adj[N];
int n, q;

int in[N], out[N], par[N], t = 0;
void dfs(int u = 0) {
  in[u] = t++;
  for (int v : adj[u]) 
    par[v] = u, dfs(v);
  out[u] = t-1;
}

int in_subtree(int u, int v) {
  return in[u] <= in[v] && out[u] >= out[v];
}

int link[N], col[N];
int find(int u) {
  if (link[u] == u) return u;
  return link[u] = find(link[u]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> par[i];
  for (int i = 1; i < n; ++i) 
    adj[par[i]].emplace_back(i);
  dfs();
  for (int i = 0; i < n; ++i) 
    link[i] = i;
  
  cin >> q;
  for (int t, u, v; q--; ) {
    cin >> t >> u >> v;
    if (t == 1) {
      col[u] = v;
    } else {
      for (;;) {
        v = find(v);  
        if (v == 0 || !col[par[v]] || col[par[v]] != col[v]) break;
        link[v] = par[v];
      }
      for (;;) {
        u = find(u);  
        if (u == 0 || !col[par[u]] || col[par[u]] != col[u]) break;
        link[u] = par[u];
      }
      cout << (u == v ? "YES\n" : "NO\n");
    }
  }
  
	return 0;
}


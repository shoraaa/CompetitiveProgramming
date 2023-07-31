#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e4 + 5;
vector<int> adj[N];
int n, m;

int bridges = 0, artis = 0;

int in[N], low[N], t = 0;
void dfs(int u, int p) {
  in[u] = low[u] = ++t;
  
  int child = 0, is_arti = 0;
  for (int v : adj[u]) {
    if (v == p) continue;
    if (in[v]) {
      low[u] = min(low[u], in[v]);
    } else {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      
      if (low[v] > in[u]) {
        bridges++;
      }
      if (p != 0 && low[v] >= in[u]) {
        is_arti = 1;
      }
      
      child++;
    }
    
  }
  
  if (p == 0 && child > 1) {
    is_arti = 1;
  }
  
  artis += is_arti;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  
  for (int i = 1; i <= n; ++i) {
    if (in[i]) continue;
    dfs(i, 0);
  }
  
  cout << artis << ' ' << bridges;
  
	return 0;
}


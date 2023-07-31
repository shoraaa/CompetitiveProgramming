#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 805;
vector<int> adj[N], scc[N], comp[N];
int deg_in[N];
int n, m;

int in[N], low[N], t = 0;

stack<int> st;
int idx[N], id = 0;

void dfs(int u) {
  in[u] = low[u] = ++t;
  st.push(u);
  for (int v : adj[u]) {
    if (idx[v]) continue;
    if (in[v]) {
      low[u] = min(low[u], in[v]);
    } else {
      dfs(v);
      low[u] = min(low[u], low[v]);
    }
  }
  
  if (low[u] == in[u]) {
    id++;
    for (;;) {
      int v = st.top(); st.pop();
      idx[v] = id;
      comp[id].emplace_back(v);
      if (v == u) break;
    }
  }
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    adj[u].emplace_back(v);
  }
  
  for (int i = 1; i <= n; ++i) {
    if (in[i]) continue;
    dfs(i);
  }
  
  for (int u = 1; u <= n; ++u) {
    for (int v : adj[u]) {
      scc[idx[u]].emplace_back(idx[v]);
    }
  }
  
  for (int i = 1; i <= id; ++i) {
    sort(scc[i].begin(), scc[i].end());
    scc[i].erase(unique(scc[i].begin(), scc[i].end()), scc[i].end());
    for (int v : scc[i]) {
      if (v == i) continue;
      deg_in[v]++;
    }
  }
  
  int res = 0;
  for (int i = 1; i <= id; ++i) {
    if (deg_in[i] == 0) {
      res += 1;
    }
  }
  cout << res;
  
  
	return 0;
}


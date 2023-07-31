#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e4 + 5;
vector<int> adj[N];
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
  
  cout << id;
  
	return 0;
}


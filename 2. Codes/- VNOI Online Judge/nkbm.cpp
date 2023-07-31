#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1005;
vector<int> adj[N];
int to[N];
int n1, n2, m;

int iter = 0, vis[N];
int dfs(int u) {
  vis[u] = iter;
  for (int v : adj[u]) if (!to[v]) {
    return to[v] = u, 1;
  }
  for (int v : adj[u]) if (vis[to[v]] != iter && dfs(to[v])) {
    return to[v] = u, 1;
  }
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n1 >> n2 >> m;
  
  int flag = 0;
  
  if (n1 > n2) {
    swap(n1, n2);
    flag = 1;
  }
  
	for (int i = 1, u, v; i <= m; ++i) {
	  cin >> u >> v;
	  if (flag) adj[v].emplace_back(u);
	  else adj[u].emplace_back(v);
	}
	
	int res = 0;
	for (int i = 1; i <= n1; ++i) {
	  iter += 1;
	  res += dfs(i);
	}
	cout << res;
	
	return 0;
}


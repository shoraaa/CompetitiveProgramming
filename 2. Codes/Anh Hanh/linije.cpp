#include<bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int N = 505;
 
vector<int> adj[N];
int match[N], vis[N];
 
int dfs(int u) {
  vis[u] = 1;
  for (int v : adj[u]) if (!match[v])
    return match[v] = u, 1;
  for (int v : adj[u]) if (!vis[match[v]] && dfs(match[v]))
    return match[v] = u, 1;
  return 0;
}
 
int n, m, k;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  if (fopen("linije.inp", "r")) 
    freopen("linije.inp", "r", stdin),
    freopen("linije.out", "w", stdout);
  cin >> n; set<int> cx, cy;
  for (int i = 0, x, y; i < n; ++i) {
    cin >> x >> y;
    adj[x].emplace_back(y);
    cx.insert(x), cy.insert(y);
  }
  
  if (cx.size() != cy.size()) 
    return cout << "Tanya", 0;
  
  int res = 0;
  for (int u : cx) {
    memset(vis, 0, sizeof(vis));
    if (dfs(u)) res += 1;
  }
  cout << (res == cx.size() ? "Antonina" : "Tanya");
  return 0;
}
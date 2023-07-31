#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
vector<int> adj[N];
int dep[N], par[N], siz[N], vis[N];
void dfs(int u = 0, int p = -1) {
  for (int v : adj[u]) if (v != p)
    dep[v] = dep[u] + 1, par[v] = u, dfs(v, u);
}
int dx, dux, v;
int size(int u, int p = -1) {
  siz[u] = 1;
  for (int v : adj[u]) if (v != p && !vis[v])
    siz[u] += size(v, u);
  return siz[u];
}
int find(int u, int s, int p = -1) {
  for (int v : adj[u]) if (v != p && !vis[v])
    if (siz[v] > s) return find(v, s, u);
  return u;
}
void solve(int u) {
  u = find(u, size(u) / 2);
  vis[u] = 1;
  cout << "d " << u + 1 << endl;
  cin >> dux;
  if (dux == 0) 
    cout << "! " << u + 1 << endl, exit(0);
  if (dx - dux == dep[u]) {
    cout << "s " << u + 1 << endl;
    cin >> v, v--;
    solve(v);
  } else solve(par[u]);
}
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  dfs();
  cout << "d 1" << endl;
  cin >> dx;
  solve(0);
	return 0;
}


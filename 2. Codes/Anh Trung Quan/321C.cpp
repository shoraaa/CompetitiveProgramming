#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
vector<int> adj[N];
int siz[N], vis[N];
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
char res[N];
void solve(int u, char c = 'A') {
  if (c == 'Z' + 1)
    cout << -1, exit(0);
  u = find(u, size(u) / 2);
  res[u] = c, vis[u] = 1;
  for (int v : adj[u]) if (!vis[v])
    solve(v, c + 1);
}
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  solve(0);
  for (int v = 0; v < n; ++v)
    cout << res[v] << ' ';
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
int n, k;
map<pair<int, int>, int> mp; int id = 0;
vector<pair<int, int>> hor[2], ver[2];
#define fi first
#define se second

int get(int r, int c) {
  int u = mp[{r, c}];
  if (!u) {
    u = ++id, mp[{r, c}] = u; 
    if (r == 0) hor[0].emplace_back(c, u);
    else if (r == n) hor[1].emplace_back(c, u);
    
    if (c == 0) ver[0].emplace_back(r, u);
    else if (c == n) ver[1].emplace_back(r, u);
  }
  return u;
}
vector<int> adj[N];
void add(int u, int v) {
  adj[u].emplace_back(v),
  adj[v].emplace_back(u);
}
int V, E;
int vis[N];
void dfs(int u) {
  V++;
  for (int v : adj[u]) {
    E++;
    if (!vis[v])
      vis[v] = 1, dfs(v);
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  if (ll(k) * k == n) 
    return cout << 0, 0;
  get(0, 0), get(0, n), get(n, 0), get(n, n);
  for (int i = 0, r, c; i < k; ++i) {
    cin >> r >> c;
    int x = get(r - 1, c - 1), y = get(r - 1, c), z = get(r, c), t = get(r, c - 1);
    add(x, y), add(y, z), add(z, t), add(t, x);
  }
  for (int t = 0; t < 2; ++t) {
    sort(hor[t].begin(), hor[t].end());
    for (int i = 0; i < hor[t].size() - 1; ++i) 
      add(hor[t][i].se, hor[t][i + 1].se);
    sort(ver[t].begin(), ver[t].end());
    for (int i = 0; i < ver[t].size() - 1; ++i) 
      add(ver[t][i].se, ver[t][i + 1].se);
  }

  for (int u = 1; u <= id; ++u) {
    sort(adj[u].begin(), adj[u].end());
    adj[u].erase(unique(adj[u].begin(), adj[u].end()), adj[u].end());
  }

  int res = 0; 
  for (int u = 1; u <= id; ++u) if (!vis[u]) {
    V = 0, E = 0;
    vis[u] = 1, dfs(u);
    res += E / 2 - V + 1;
  }
  cout << res - k;
	return 0;
}


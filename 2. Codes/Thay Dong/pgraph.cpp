#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e6 + 5;
int s[N];
int f, M;
vector<int> edges[N];
int w[N];

map<pair<int, int>, int> mp; int id = 0;
pair<int, int> vert[N];
#define fi first
#define se second
int get(int u, int v) {
  if (u > v) swap(u, v);
  int i = mp[{u, v}];
  if (!i) 
    mp[{u, v}] = i = ++id,
    vert[i] = {u, v};
  return i;
}

int out[N], vis[N];
vector<pair<int, int>> adj[N];
void dfs(int u) {
  
  for (auto& p : adj[u]) if (~p.fi && !vis[p.fi]) {
    vis[p.fi] = 1;
    dfs(p.fi);
  }
  
  int cur = s[u];
  for (auto& p : adj[u]) if (~w[p.se]) {
    cur -= w[p.se];
    if (cur < 0) cur += M;
  }
  cur %= M;
  int flag = 0;
  for (auto& p : adj[u]) if (!~w[p.se]) {
    if (!flag) w[p.se] = cur, flag = 1;
    else w[p.se] = 0;
  }

}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> f >> M;
  for (int i = 0, k; i < f; ++i) {
    cin >> k; vector<int> v(k); 
    for (int j = 0; j < k; ++j)
      cin >> v[j];
    for (int j = 0; j < k - 1; ++j) 
      edges[get(v[j], v[j + 1])].emplace_back(i);
    edges[get(v[k - 1], v[0])].emplace_back(i);
    cin >> s[i];
  }
  int flag = 0;
  for (int i = 1, u, v; i <= id; ++i) if (edges[i].size() == 1) {
    u = edges[i][0];
    out[u] = 1; flag = 1;
    adj[u].emplace_back(-1, i);
  } else {
    u = edges[i][0], v = edges[i][1];
    adj[u].emplace_back(v, i),
    adj[v].emplace_back(u, i);
  }
  if (!flag) 
    return cout << -1, 0;
  memset(w, -1, sizeof(w));
  for (int u = 0; u < f; ++u) if (out[u] && !vis[u]) 
    vis[u] = 1, dfs(u);  
  for (int i = 1; i <= id; ++i) {
    int u = vert[i].fi, v = vert[i].se;
    cout << u << ' ' << v << ' ' << w[i] << '\n';
  }
  return 0;
}

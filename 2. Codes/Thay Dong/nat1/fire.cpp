#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const ld inf = 1e18;

const int N = 255, L = 200;
int n;
vector<pair<int, ld>> adj[N];
int vis[N]; ld dis[N];
pair<int, int> point[N];

int id = 0;
vector<int> source;
map<pair<int, int>, int> mp;
int pos(int x, int y) {
  if (mp[{x, y}]) return mp[{x, y}];
  id += 1; point[id] = make_pair(x, y);
  if (x % 2 == 0 && y % 2 == 0)
    source.emplace_back(id);
  return mp[{x, y}] = id;
}

vector<tuple<int, int, ld>> edges;
void add(int u, int v, ld w) {
  adj[u].emplace_back(v, w), 
  adj[v].emplace_back(u, w);
  edges.emplace_back(u, v, w);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; ld w;
  for (int i = 0, x, y, u, v; i < n; ++i) {
    cin >> x >> y >> u >> v >> w;
    x += L, y += L, u += L, v += L;
    x *= 2, y *= 2, u *= 2, v *= 2;
    if (make_pair(x, y) > make_pair(u, v)) swap(x, u), swap(y, v);
    if (x != u && y != v) {
      int hx = x + 1, hy = y + (v - y) / 2;
      add(pos(x, y), pos(hx, hy), w / 2.0);
      add(pos(u, v), pos(hx, hy), w / 2.0);
    } else {
      add(pos(x, y), pos(u, v), w);
    }
  }
  ld ans = inf;
  for (int s : source) {
    for (int u = 1; u <= id; ++u) 
      dis[u] = inf, vis[u] = 0;
    priority_queue<pair<ld, int>> q;
    dis[s] = 0; q.emplace(0, s);
    while (!q.empty()) {
      int u; ld d; tie(d, u) = q.top(); q.pop();
      if (vis[u]) continue;
      vis[u] = 1;
      for (auto& p : adj[u]) {
        ld w; int v; tie(v, w) = p;
        if (dis[u] + w < dis[v]) 
          dis[v] = dis[u] + w,
          q.emplace(-dis[v], v);
      }
    }
    ld res = 0;
    for (int u = 1; u <= id; ++u) 
      res = max(res, dis[u]);
    for (auto& p : edges) {
      int u, v; ld w; tie(u, v, w) = p; 
      if (dis[u] > dis[v]) swap(u, v);
      if (dis[v] - dis[u] >= w) continue;
      res = max(res, dis[v] + (w - dis[v] + dis[u]) / 2.0); 
    }
    ans = min(ans, res);
  }
  cout << fixed << setprecision(2) << ans;
	return 0;
}


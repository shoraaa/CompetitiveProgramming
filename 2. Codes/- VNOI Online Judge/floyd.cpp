#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 105;
const int INF = 1e9 + 9;

vector<pair<int, int>> adj[N];
int n, m;

priority_queue<pair<int, int>> q;
int dis[N], to[N];

void dijkstra(int s, int t, int tp) {
  for (int i = 1; i <= n; ++i) {
    dis[i] = INF;
  }
  dis[s] = 0;
  q.emplace(0, s);

  while (!q.empty()) {
    int d, u; tie(d, u) = q.top(); 
    q.pop(); d = -d;
    if (d != dis[u]) continue;
    
    for (auto& e : adj[u]) {
      int v, w; tie(v, w) = e;
      if (d + w < dis[v]) {
        dis[v] = d + w;
        to[v] = u;
        q.emplace(-dis[v], v);
      }
    }
    
  }
  
  if (tp == 0) {
    cout << dis[t] << '\n';
  } else {
    vector<int> path;
    for (int v = t;; v = to[v]) {
      path.emplace_back(v);
      if (v == s) break;
    }
    reverse(path.begin(), path.end());
    
    cout << path.size() << ' ';
    for (int v : path) cout << v << ' ';
    cout << '\n';
  }
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int q;
  cin >> n >> m >> q;
  for (int i = 1, u, v, w; i <= m; ++i) {
    cin >> u >> v >> w;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  
  for (int i = 1, t, u, v; i <= q; ++i) {
    cin >> t >> u >> v;
    dijkstra(u, v, t);
  }
  
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
const ll inf = 1e18 + 9;

#define int ll

vector<pair<int, int>> adj[N];
int n, m, X;
int a[N], dis[N];
  
signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("socbay.inp", "r"))
    freopen("socbay.inp", "r", stdin),
    freopen("socbay.out", "w", stdout);
    
  cin >> n >> m >> X;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    adj[u].emplace_back(v, w),
    adj[v].emplace_back(u, w);
  
  priority_queue<pair<int, int>> q;
  fill(dis, dis + n, inf);
  q.emplace(0, 0); dis[0] = 0; 
  while (!q.empty()) {
    int d, u; tie(d, u) = q.top(); q.pop();
    if (-d != dis[u]) continue;
    
    int cur = min(a[u], max(0LL, X - dis[u]));
    
    if (u == n-1) 
      return cout << dis[u] + a[u] - cur << '\n', 0;
    
    for (auto& p : adj[u]) {
      int v, w; tie(v, w) = p;
      int cost = [&]() {
        if (cur - w > a[v]) return w + (cur - (a[v] + w));
        if (cur - w >= 0) return w;
        if (a[u] - w >= 0) return 2 * w - cur;
        return inf;
      }();
      if (dis[u] + cost < dis[v]) 
        dis[v] = dis[u] + cost, q.emplace(-dis[v], v);
    }
  }
    
  cout << -1 << '\n';
	return 0;
}


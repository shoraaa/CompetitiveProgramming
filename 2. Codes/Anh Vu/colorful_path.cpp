#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
vector<tuple<int, int, int>> adj[N];
ll dis[N][2]; int cnt[N], col[N][2];
int n, m, k, C;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> C;
  for (int i = 0, u, v, w, c; i < m; ++i) {
    cin >> u >> v >> w >> c; u--; v--;
    adj[u].emplace_back(v, w, c);
  }
  int s; cin >> s; s--;
  memset(dis, 0x3f, sizeof(dis)); ll inf = dis[0][0];
  priority_queue<tuple<ll, int, int>> q;
  q.emplace(0, -1, s); 
  int u, c; ll d;
  while (!q.empty()) {
    tie(d, c, u) = q.top(); d = -d; q.pop();
    if (cnt[u] > 1 || (cnt[u] == 1 && c == col[u][0])) continue;
    dis[u][cnt[u]] = d, col[u][cnt[u]] = c, cnt[u]++; 
    for (auto& e : adj[u]) {
      int v, w, nc; tie(v, w, nc) = e;
      if (c == nc) continue;
      q.emplace(-(d + w), nc, v);
    }
  }
  cin >> k;
  for (int i = 0, t; i < k; ++i)
    cin >> t, t--, cout << (dis[t][0] == inf ? -1 : dis[t][0]) << '\n';
	return 0;
}
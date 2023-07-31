#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "paths";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 500 + 5;
const ll llinf = 1e18;
struct C {
  int v, w;
  C(int v, int w): v(v), w(w) {}
  bool operator < (const C& c) {
    return w < c.w;
  }
};
vector<C> adj[N];
ll d[N][N];
int vis[N], cnt[N];
int n, m, T;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
  cin >> T >> n >> m;
  for (int u = 0; u < n; ++u) {
    fill(begin(d[u]), end(d[u]), llinf);
    d[u][u] = 0;
  }
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    d[u][v] = d[v][u] = w,
    adj[u].emplace_back(v, w),
    adj[v].emplace_back(u, w);
    
  for (int k = 0; k < n; ++k) for (int u = 0; u < n; ++u) if (d[u][k] != llinf)
    for (int v = 0; v < n; ++v) if (d[k][v] != llinf) {
      if (d[u][k] + d[k][v] < d[])
    }
      d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
  
  for (int s = 0; s < n; ++s) {
    
    memset(cnt, 0, sizeof(cnt));
    for (int u = 0; u < n; ++u) for (C& c : adj[u]) 
      if (d[s][u] + c.w == d[s][c.v]) cnt[c.v]++;
    
    for (int t = s+1; t < n; ++t) {
      int res = 0;
      for (int v = 0; v < n; ++v) if (d[s][t] == d[s][v] + d[v][t])
        res += cnt[v];
      cout << res << " \n"[t == n-1];
    }
  }
	return 0;
}


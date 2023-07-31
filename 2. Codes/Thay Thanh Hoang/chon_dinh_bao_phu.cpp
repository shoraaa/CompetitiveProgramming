#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005;
const int INF = 2e9 + 5;

vector<int> adj[N];
int c[N], t[N];
int n;

ll f[N][N], g[N][N];

ll cmin(ll& x, ll y) {
  return x > y ? x = y, 1 : 0;
}

void dfs(int u = 0, int p = -1) {
  // f[u][i] = min f[v*][i + 1] + sum g[v][i - 1]
  // g[u][i] = sum g[v][i - 1]
  // g[u][0] = f[u][-1]
  for (int v : adj[u]) if (v != p)
    dfs(v, u);

  for (int i = 0; i < n; ++i) {
    for (int v : adj[u]) if (v != p) {
      ll val = i == 0 ? f[v][0] : g[v][i - 1];
      g[u][i] += val;
    }
  }
  
  for (int i = 0; i < n; ++i) {
    if (i < t[u]) cmin(f[u][i], g[u][i] + c[i]);
    for (int v : adj[u]) if (v != p) {
      ll val = i == 0 ? f[v][0] : g[v][i - 1];
      cmin(f[u][i], g[u][i] - val + f[v][i + 1]);
    }
  }
  
  for (int i = n - 2; i >= 0; --i)
    cmin(f[u][i], f[u][i + 1]);
  cmin(g[u][0], f[u][0]);
  for (int i = 1; i < n; ++i)
    cmin(g[u][i], g[u][i - 1]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> c[i];
  for (int i = 0; i < n; ++i)
    cin >> t[i];
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j <= n + 1; ++j)
      f[i][j] = INF;
  dfs();
  cout << (f[0][0] == INF ? -1 : f[0][0]);
	return 0;
}


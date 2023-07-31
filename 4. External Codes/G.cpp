#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e4 + 5, inf = 1e9;
int a[N], dp[2][N];
vector<int> pos[N];
int comp[N];
int n, m;
vector<int> adj[N];
int vis[N]; 
int cc = 0;

int cmax(int& x, int y) {
  return x < y ? x = y, 1 : 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> a[i], a[i]--;
  for (int i = 0, u, v; i < m; ++i) 
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  for (int i = 0; i < n; ++i) if (!vis[i]) {
    queue<int> q; q.emplace(i);
    while (!q.empty()) {
      int p = q.front(); q.pop();
      comp[a[p]] = cc; vis[p] = 1; pos[cc].emplace_back(p);
      for (int v : adj[p]) if (!vis[v])
        q.emplace(v);
    }
    cc++;
  }
  
  for (int i = 0; i < cc; ++i) 
    sort(pos[i].begin(), pos[i].end());
  
  for (int i = 0; i < n; ++i) dp[0][i] = -inf;
  dp[0][0] = 0; int res = 0;
  for (int i = 0; i < n; ++i) {
    int cur = i&1, nxt = cur^1;
    for (int j = 0; j < n; ++j) dp[nxt][j] = -inf;
    for (int j = 0, p = 0; j < n; ++j) if (dp[cur][j] != -inf) {
      cmax(dp[nxt][j], dp[cur][j]);
      
      while (p < pos[comp[i]].size() && pos[comp[i]][p] < j) p++;
      if (p == pos[comp[i]].size()) continue;
      cmax(dp[nxt][pos[comp[i]][p]], dp[cur][j] + 1);
      cmax(res, dp[cur][j] + 1);
    }
  }
  cout << res;

	return 0;
}


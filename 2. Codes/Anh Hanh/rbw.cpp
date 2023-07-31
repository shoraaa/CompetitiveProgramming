#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5, M = 998244353;
inline int sum(int x, int y) {
  x += y; if (x >= M) x -= M; return x;
}
inline int dif(int x, int y) {
  x -= y; if (x < 0) x += M; return x;
}
inline void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
inline void sub(int& x, int y) {
  x -= y; if (x < 0) x += M;
}
inline int mul(ll x, ll y) {
  return x * y % M;
}

int dp[N][2], f[2][2], g[2][2], h[2][2];
vector<int> adj[N];
int n;
void dfs(int u = 0) {
  for (int v : adj[u]) dfs(v);
  sort(adj[u].begin(), adj[u].end());
  int m = adj[u].size(); 
  f[0][0] = g[0][0] = h[0][0] = 1, f[0][1] = g[0][1] = h[0][1] = 0; 
  int cur = 0;
  for (int i = 1; i <= m; ++i) {
    int v = adj[u][i - 1], pre = cur; cur ^= 1;
    for (int t = 0; t < 2; ++t) 
      f[cur][t] = sum(mul(f[pre][t], sum(dp[v][0], 1)), mul(f[pre][t^1], dp[v][1])),
      g[cur][t] = sum(mul(g[pre][t^1], dp[v][0]), g[pre][t]), 
      h[cur][t] = sum(mul(h[pre][t^1], dp[v][1]), h[pre][t]);
  }
  dp[u][1] = dif(mul(f[cur][0], 2), sum(g[cur][0], g[cur][1]));
  dp[u][0] = dif(mul(f[cur][1], 2), h[cur][1]);
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("rbw.inp", "r")) 
    freopen("rbw.inp", "r", stdin),
    freopen("rbw.out", "w", stdout);
  int subtask; cin >> subtask;
  int n; cin >> n;
  for (int i = 1, p; i < n; ++i)
    cin >> p, p--,
    adj[p].emplace_back(i);
  dfs();
  add(dp[0][0], dp[0][1]);
  cout << dp[0][0];
	return 0;
}


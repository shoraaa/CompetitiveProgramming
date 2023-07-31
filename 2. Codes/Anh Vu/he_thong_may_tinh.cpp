#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int cmin(ll& x, ll y) {
  return x > y ? x = y, 1 : 0;
}

const int N = 5005;
const ll inf = 1e15;
vector<int> adj[N];
int sz[N], a[N];
ll dp[N][N][2], nxt[N][2];

int n;

void dfs(int u, int p = -1) {
  sz[u] = 1;
  dp[u][0][a[u] < 0] = a[u];

  for (int v : adj[u]) if (v != p) { 
    dfs(v, u); 
    
    for (int i = 0; i < n; ++i) nxt[i][0] = nxt[i][1] = inf;

    for (int i = 0; i < sz[u]; ++i) for (int x = 0; x < 2; ++x) {
      for (int j = 0; j < sz[v]; ++j) for (int y = 0; y < 2; ++y) {
       
        // ko cat canh noi den v
        cmin(nxt[i + j][x | y], dp[u][i][x] + dp[v][j][y]);
        // cat canh noi den v
        if (dp[v][j][y] < 0 || (y == 0 && dp[v][j][y] != inf))
          cmin(nxt[i + j + 1][x], dp[u][i][x]);
          
      }
    }
    
    sz[u] += sz[v];
    for (int i = 0; i < sz[u]; ++i) 
      dp[u][i][0] = nxt[i][0], dp[u][i][1] = nxt[i][1];
    
  }
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
    dp[i][j][0] = dp[i][j][1] = inf;
  dfs(0);
  for (int i = 0; i < n; ++i)
    if (dp[0][i][0] != inf || dp[0][i][1] < 0) 
      return cout << i, 0;
	return 0;
}


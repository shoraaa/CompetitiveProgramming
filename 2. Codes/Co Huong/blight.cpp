#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
vector<int> adj[N];
int a[N]; ll dp[N][4]; // {ko chon, chon, ko chon nhung cha no chon, ko chon nhung con no chon}
int n;

void dfs(int u = 0, int p = -1) {
  dp[u][0] = 0; dp[u][1] = dp[u][2] = dp[u][3] = a[u]; 
  ll max_val = -1e18;
  for (int v : adj[u]) if (v != p) {
    dfs(v, u);
    dp[u][0] += max({dp[v][0], dp[v][3]});
    dp[u][1] += max(dp[v][1], dp[v][2]);
    dp[u][2] += max({dp[v][0], dp[v][1], dp[v][3]});
    dp[u][3] += max({dp[v][0], dp[v][1], dp[v][3]});
    max_val = max(max_val, dp[v][1] - max({dp[v][0], dp[v][1], dp[v][3]}));
  }
  dp[u][3] += max_val;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("blight.inp", "r"))
    freopen("blight.inp", "r", stdin),
    freopen("blight.out", "w", stdout);
  
  int T; cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 0; i < n; ++i)
      cin >> a[i], adj[i].clear();
    for (int i = 0, u, v; i < n-1; ++i)
      cin >> u >> v, u--, v--,
      adj[u].emplace_back(v),
      adj[v].emplace_back(u);
    memset(dp, -0x3f, sizeof(dp));
    dfs();
    cout << max({dp[0][0], dp[0][1], dp[0][3]}) << '\n';
  }
	return 0;
}


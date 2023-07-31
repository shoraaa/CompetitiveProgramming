#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
vector<int> adj[N];
int n;
int a[N], b[N];
ll dp[N][2];

void dfs(int u = 0, int p = -1) {
  ll x = a[u]; vector<int> sub;
  for (int v : adj[u]) if (v != p) {
    dfs(v, u);
    x += dp[v][1]; 
    sub.emplace_back(-dp[v][1] + dp[v][0]);
  }
  dp[u][0] = dp[u][1] = x;
  sort(sub.begin(), sub.end());
  if (sub.size() >= b[u]) {
    ll cur = x - a[u];
    for (int i = 0; i < b[u]; ++i) cur += sub[i];
    dp[u][0] = min(dp[u][0], cur);
  } 
  if (sub.size() >= b[u] - 1) {
    ll cur = x - a[u];
    for (int i = 0; i < b[u] - 1; ++i) cur += sub[i];
    dp[u][1] = min(dp[u][1], cur);
  }  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0; i < n; ++i)
    cin >> b[i];
  dfs();
  cout << dp[0][0];
	return 0;
}


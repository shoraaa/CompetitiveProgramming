#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5;
vector<int> adj[N];
int a[N], par[N][20];
int n, m;
ll res = 0;
void dfs(int u, int p) {
  par[u][0] = p;
  ll val = a[p];
  for (int k = 1; k < 20; ++k) 
    par[u][k] = par[par[u][k-1]][k-1],
    val = min(val, ll(k + 1) * a[par[u][k]]);
  if (u != p) res += val + a[u];
  for (int v : adj[u]) if (v != p)
    dfs(v, u);
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
  m = min_element(a, a + n) - a;
  dfs(m, m);
  cout << res;
	return 0;
}


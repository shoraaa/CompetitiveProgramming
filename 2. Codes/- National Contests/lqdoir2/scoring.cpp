#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, M = 1e9 + 7;
vector<int> adj[N];
int n, k, root;
int a[N], sz[N], dp[N];

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

ll fac[N], inv[N];
ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * inv[k] % M * inv[n-k] % M;
}
ll sC(ll n, int k) {
  // n! / (n-k)! = n-k+1 * n-k+2..
  ll res = 1;
  for (int i = n-k+1; i <= n; ++i)
    res = res * i % M;
  // /k!
  res = res * inv[k] % M;
  return res;
}

void dfs(int u, int p = -1) {
  sz[u] = 1;
  for (int v : adj[u]) if (v != p)
    dfs(v, u), sz[u] += sz[v];
  int tot = sz[u] - 1; dp[u] = 1;
  for (int v : adj[u]) if (v != p) {
    dfs(v, u);
    dp[u] *= C(tot, sz[v]) * dp[v] % M; 
    dp[u] %= M; tot -= sz[v];
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("scoring.inp", "r"))
    freopen("scoring.inp", "r", stdin),
    freopen("scoring.out", "w", stdout);
  cin >> n >> k; root = 0;
  
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= k; ++i)
    fac[i] = fac[i-1] * i % M,
    inv[i] = pw(fac[i], M-2);
    
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  for (int i = 0; i < n; ++i)
    cin >> a[i], root = a[i] < a[root] ? i : root;
  dfs(root);
  cout << sC(k, n) * dp[root] % M;
	return 0;
}


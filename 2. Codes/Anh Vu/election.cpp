#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
vector<int> adj[N];
int par[N][20], dep[N], in[N], out[N];
int t = 1;
void dfs(int u = 1, int p = 1) {
  in[u] = t++;
  if (u != 1) adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
  par[u][0] = p; dep[u] = dep[p] + 1;
  for (int i = 1; i < 20; ++i)
    par[u][i] = par[par[u][i-1]][i-1];
  for (int v : adj[u])
    dfs(v, u);
  out[u] = t;
}
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int i = 19; ~i; --i)
    if (dep[par[u][i]] >= dep[v]) u = par[u][i];
  if (u == v) return u;
  for (int i = 19; ~i; --i)
    if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
  return par[u][0];
}
struct Path {
  int u, v, w;
  Path(int u, int v, int w): u(u), v(v), w(w) {}
};
vector<Path> pat[N];
ll dp[N], bit[N], sum[N];
int n, m;
ll get(int u) {
  ll res = 0;
  for (int i = in[u]; i; i -= i & -i)
    res += bit[i];
  return res;
}
void update(int i, ll x) {
  for (; i <= n; i += i & -i)
    bit[i] += x;
}
void add(int u, ll x) {
  update(in[u], x), update(out[u], -x);
}
void calc(int u = 1) {
  for (int v : adj[u])
    calc(v), sum[u] += dp[v];
  dp[u] = sum[u];
  for (auto& p : pat[u]) 
    dp[u] = max(dp[u], get(p.u) + get(p.v) + p.w + sum[u]);
  add(u, sum[u] - dp[u]);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  dfs();
  cin >> m;
  for (int i = 0, u, v, w; i < m; ++i) 
    cin >> u >> v >> w,
    pat[lca(u, v)].emplace_back(u, v, w);
  calc();
  cout << dp[1];
	return 0;
}


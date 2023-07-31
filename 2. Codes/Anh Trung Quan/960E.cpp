#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5, M = 1e9 + 7;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M; 
}
void sub(int& x, int y) {
  x -= y; if (x < 0) x += M;
}
int sum(int x, int y) {
  x += y; if (x >= M) x -= M; return x;
}
int dif(int x, int y) {
  x -= y; if (x < 0) x += M; return x;
}
int neg(int x) {
  return -x + M;
}
int mul(ll x, ll y) {
  return x * y % M;
}
vector<int> adj[N];
int a[N];
int n;
int siz[N], vis[N];
int size(int u, int p = -1) {
  siz[u] = 1;
  for (int v : adj[u]) if (v != p && !vis[v])
    siz[u] += size(v, u);
  return siz[u];
}
int find(int u, int s, int p = -1) {
  for (int v : adj[u]) if (v != p && !vis[v])
    if (siz[v] * 2 >= s) return find(v, s, u);
  return u;
}
int cnt[2], val[2], res = 0;
void dfs(int u, int p, int d = 1, int cur = 0) {
  cur = dif(a[u], cur); 
  if (d) add(res, cur);
  for (int v : adj[u]) if (v != p && !vis[v])
    dfs(v, u, d ^ 1, cur);
}
void update(int u, int p, int d, int cur) {
  cur = dif(a[u], cur);
  add(val[d], cur), cnt[d]++;
  for (int v : adj[u]) if (v != p && !vis[v])
    update(v, u, d ^ 1, cur);
}
void get(int u, int p, int d, int cur) {
  if (d) add(cur, a[u]);
  else sub(cur, a[u]);
  add(res, sum(mul(d ? cur : neg(cur), cnt[d^1]), val[d^1]));
  for (int v : adj[u]) if (v != p && !vis[v])
    get(v, u, d ^ 1, cur);
}
void solve(int u) {
  u = find(u, size(u));
  dfs(u, -1); 
  cnt[0] = cnt[1] = val[0] = val[1] = 0;
  for (int v : adj[u]) if (!vis[v])
    get(v, u, 1, 0), update(v, u, 0, a[u]);
  vis[u] = 1;  
  for (int v : adj[u]) if (!vis[v])
    solve(v);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int v = 0; v < n; ++v)
    cin >> a[v], add(a[v], M);
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  solve(0); res = mul(res, 2);
  for (int v = 0; v < n; ++v)
    sub(res, a[v]);
  cout << res;
	return 0;
}
 
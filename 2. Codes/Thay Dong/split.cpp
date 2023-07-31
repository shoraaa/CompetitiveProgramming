#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define fi first
#define se second
const int N = 1e5 + 5;
vector<int> adj[N];
int n, m; pair<int, int> x[3];

int low[N], in[N], siz[N], par[N], t = 0;
vector<int> ans;
int dfs1(int u, pair<int, int>& x) {
  ans[u] = x.se; x.fi--;
  if (x.fi == 0) return 1;
  for (int v : adj[u]) if (par[v] == u)
    if (dfs1(v, x)) return 1;
  return 0;
}
int dfs2(int u, pair<int, int>& y) {
  ans[u] = y.se; y.fi--;
  if (y.fi == 0) return 1;
  for (int v : adj[u]) if (ans[v] == x[2].se)
    if (dfs2(v, y)) return 1;
  return 0;
}
int dfs(int u, int p = -1) {
  int flag = 1;
  in[u] = low[u] = ++t, siz[u] = 1;
  for (int v : adj[u]) if (v != p) {
    if (in[v]) low[u] = min(low[u], in[v]); // back-edge
    else {
      par[v] = u;
      if (dfs(v, u)) return 1;
      low[u] = min(low[u], low[v]);
      siz[u] += siz[v];
      flag &= siz[v] < x[0].fi;
    }
  }
  flag &= siz[u] >= x[0].fi;
  if (!flag) return 0;
  int P1 = siz[u], P2 = n - siz[u];
  for (int v : adj[u]) if (par[v] == u && low[v] < in[u] && P2 < x[0].fi)
    P1 -= siz[v], P2 += siz[v];
  if (P2 < x[0].fi) return 0;
  if (P1 > P2) swap(x[0], x[1]);
  dfs1(u, x[0]); dfs2(p, x[1]);
  return 1;
}

vector<int> find_split(int _n, int a, int b, int c, vector<int> p, vector<int> q) {
  n = _n; m = p.size();
  x[0] = {a, 1}, x[1] = {b, 2}, x[2] = {c, 3};
  sort(x, x + 3);
  for (int i = 0, u, v; i < m; ++i)
    u = p[i], v = q[i],
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  ans = vector<int>(n, x[2].se);
  if (dfs(0)) 
    return ans;
  return vector<int>(n, 0);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int n, m, a, b, c; 
  cin >> n >> m >> a >> b >> c;
  vector<int> p(m), q(m);
  for (int i = 0; i < m; ++i)
    cin >> p[i] >> q[i];
  vector<int> result = find_split(n, a, b, c, p, q);
  for (int x : result) cout << x << ' ';
	return 0;
}


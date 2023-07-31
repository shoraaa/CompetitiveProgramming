#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
vector<int> adj[N];
int n, q;

int dep[N], par[N][17];
void dfs(int u = 0, int p = -1) {
  for (int v : adj[u]) if (v != p) {
    dep[v] = dep[u] + 1;
    par[v][0] = u;
    for (int i = 1; i < 17; ++i) 
      par[v][i] = par[par[v][i - 1]][i - 1];
    dfs(v, u);
  }
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int i = 16; ~i; --i) if (dep[par[u][i]] >= dep[v]) u = par[u][i];
  if (u == v) return u;
  for (int i = 16; ~i; --i) if (par[u][i] != par[v][i])
    u = par[u][i], v = par[v][i];
  return par[u][0];
}

ll sum(ll l, ll r) {
  return (r - l + 1) * (r + l) / 2;
}

ll solve(int i, int j, int z, ll a, ll b) {
  ll c = dep[j] + dep[z] - 2 * dep[lca(j, z)]; 
  ll d = dep[i] + dep[z] - 2 * dep[lca(i, z)];
  
  ll x1 = min(d, (b + 2*b*d + 2*b*c - a) / ((a + b) * 2));
  ll x2 = min(d, (3*b + 2*b*d + 2*b*c + a - 1) / ((a + b) * 2));
  
  return min(sum(1, x1) * a + sum(c + 1, c + d - x1) * b,
             sum(1, x2) * a + sum(c + 1, c + d - x2) * b) + sum(1, c) * a;
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  dfs();
  
  for (int u, i, j, a, b; q--;) {
    cin >> u >> i >> j >> a >> b; u--; i--; j--;
    int z = max({make_pair(dep[lca(u, i)], lca(u, i)), 
                 make_pair(dep[lca(i, j)], lca(i, j)),
                 make_pair(dep[lca(j, u)], lca(j, u))}).second;
    cout << min(solve(i, j, z, a, b), solve(j, i, z, a, b)) << '\n';
  }
	return 0;
}


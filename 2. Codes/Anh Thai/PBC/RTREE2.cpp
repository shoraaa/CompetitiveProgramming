#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
vector<int> adj[N];
pair<int, int> edges[N];
int par[N], nxt[N], in[N], dep[N], siz[N];
int n, m;

int t = 1;
void dfs1(int u = 0) {
  siz[u] = 1;
  for (int& v : adj[u]) {
    adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
    dfs1(v), siz[u] += siz[v];
    if (siz[v] > siz[adj[u][0]]) swap(adj[u][0], v);
  }
}

void dfs2(int u = 0) {
  in[u] = t++;
  for (int v : adj[u]) {
    nxt[v] = v == adj[u][0] ? nxt[u] : v;
    dep[v] = dep[u] + 1, par[v] = u, dfs2(v);
  }
}

int bit[N];
void add(int i, int j) {
  // bit[i]++, bit[j+1]--;
  for (; i <= n; i += i & -i) bit[i]++;
  for (j++; j <= n; j += j & -j) bit[j]--;
}

void update(int u, int v) {
  if (u == v) return;
  for (; nxt[u] != nxt[v];) {
    if (dep[nxt[u]] < dep[nxt[v]]) swap(u, v);
    add(in[nxt[u]], in[u]), u = par[nxt[u]];
  }
  if (dep[u] < dep[v]) swap(u, v);
  add(in[v] + 1, in[u]);
}

int get(int i) {
  int res = 0;
  for (; i; i -= i & -i) res += bit[i];
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u),
    edges[i] = {u, v};
  dfs1(), dfs2();
  for (int i = 0, t, j, u, v; i < m; ++i) {
    cin >> t;
    if (t == 1) {
      cin >> u >> v, u--, v--;
      update(u, v);
    } else {
      cin >> j, j--;
      tie(u, v) = edges[j];
      if (dep[u] < dep[v]) swap(u, v);
      cout << get(in[u]) << '\n';
    }
  }
	return 0;
}


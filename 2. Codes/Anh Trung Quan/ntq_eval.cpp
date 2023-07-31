#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;

vector<pair<int, int>> adj[N], mst[N];
int from[N], to[N], weight[N];

struct Cmp {
  bool operator () (int i, int j) {
    return weight[i] < weight[j];
  }
};

int n, m;

int lin[N], siz[N], in_mst[N];
int find(int u) {
  if (u == lin[u]) return u;
  return lin[u] = find(lin[u]);
}
int unite(int u, int v) {
  u = find(u), v = find(v);
  if (u == v) return 0;
  if (siz[u] < siz[v]) swap(u, v);
  lin[v] = u, siz[u] += siz[v]; 
  return 1;
}

int par[N][20], val[N][20], dep[N];
int in[N], out[N], t = 0;
void dfs(int u, int p = -1) {
  in[u] = t++;
  for (auto& pi : mst[u]) {
    int v = pi.first, w = weight[pi.second];
    if (v == p) continue;
    dep[v] = dep[u] + 1;
    val[v][0] = w; par[v][0] = u;
    for (int k = 1; k < 20; ++k)
      par[v][k] = par[par[v][k-1]][k-1],
      val[v][k] = max(val[v][k-1], val[par[v][k-1]][k-1]);
    dfs(v, u);
  }
  out[u] = t-1;
}

int in_subtree(int v, int u) {
  // v nam trong subtree u
  return in[u] <= in[v] && out[v] <= out[u];
}

int get(int u, int v) {
  if (dep[u] > dep[v]) swap(u, v);
  int res = 0;
  for (int k = 19; ~k; --k) if (dep[par[v][k]] >= dep[u]) 
    res = max(res, val[v][k]), v = par[v][k];
  if (u == v) return res;
  for (int k = 19; ~k; --k) if (par[u][k] != par[v][k])
    res = max(res, val[u][k]), res = max(res, val[v][k]),
    u = par[u][k], v = par[v][k];
  res = max(res, val[u][0]), res = max(res, val[v][0]);
  return res;
}

int dp[N];
set<pair<int, int>> dfs1(int u, int p = -1) {
  set<pair<int, int>> cur;
  for (auto& pi : mst[u]) {
    int v = pi.first;
    if (v == p) continue;
    set<pair<int, int>> nxt = dfs1(v, u);
    if (nxt.size() > cur.size()) swap(nxt, cur);
    for (auto& edge : nxt) cur.insert(edge);
  }
  for (auto& pi : adj[u]) {
    int v = pi.first, i = pi.second;
    if (in_mst[i]) continue;
    if (in_subtree(v, u)) cur.erase({weight[i], i});
    else cur.insert({weight[i], i});
  }
  dp[u] = cur.empty() ? int(1e9) : cur.begin()->first;
  return cur;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0, u, v, w; i < m; ++i) {
    cin >> u >> v >> w; u--; v--;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
    from[i] = u, to[i] = v, weight[i] = w;
  }
  vector<int> order(m); iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), Cmp());
  for (int i = 0; i < n; ++i) lin[i] = i, siz[i] = 1;
  for (int i : order) {
    int u = from[i], v = to[i];
    if (unite(u, v))
      mst[u].emplace_back(v, i),
      mst[v].emplace_back(u, i),
      in_mst[i] = 1;
  }
  dfs(0); dfs1(0);
  for (int i = 0; i < m; ++i) {
    if (!in_mst[i]) 
      cout << get(from[i], to[i]) << '\n'; 
    else {
      int u = from[i], v = to[i]; if (dep[u] > dep[v]) swap(u, v);
      cout << dp[v] << '\n';
    }
  }
	return 0;
}


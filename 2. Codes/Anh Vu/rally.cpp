#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5;
vector<int> adj[N], rev[N];
int pos[N], topo[N], End[N], start[N], f[N], g[N], t;
int n, m;

void dfs(int u) {
  for (int v : adj[u]) 
    if (!pos[v]) dfs(v);
  pos[u] = t--; 
  topo[pos[u]] = u;
}

int st[N * 2];
void update(int x, int y, int w, int k = 0, int l = 1, int r = n) {
  if (l > y || r < x) return;
  if (l >= x && r <= y) return st[k] = max(st[k], w), void();
  int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
  update(x, y, w, lc, l, m);
  update(x, y, w, rc, m+1, r);
}

int get(int x, int k = 0, int l = 1, int r = n) {
  if (l == r) return st[k];
  int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
  if (x <= m) return max(st[k], get(x, lc, l, m));
  else return max(st[k], get(x, rc, m+1, r));
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  vector<pair<int, int>> ed;
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    rev[v].emplace_back(u),
    ed.emplace_back(u, v);
  t = n;
  for (int u = 0; u < n; ++u)
    if (!pos[u]) dfs(u); 
  for (int i = 1; i <= n; ++i) {
    for (int v : rev[topo[i]]) End[i] = max(End[i], End[pos[v]] + 1);
    f[i] = max(f[i-1], End[i]);
  }
  for (int i = n; i; --i) {
    for (int v : adj[topo[i]]) start[i] = max(start[i], start[pos[v]] + 1);
    g[i] = max(g[i+1], start[i]);
  }
  for (auto& e : ed) {
    int u, v; tie(u, v) = e;
    if (pos[u] > pos[v]) swap(u, v);
    update(pos[u] + 1, pos[v] - 1, End[pos[u]] + 1 + start[pos[v]]);
  }
  pair<int, int> res = {n + 1, -1};
  for (int i = 1; i <= n; ++i) 
    res = min(res, {max({f[i-1], g[i+1], get(i)}), topo[i]});
  cout << res.second+1 << ' ' << res.first;
	return 0;
}


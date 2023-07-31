#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5;

struct Edge {
  int u, v, l, r, i;
  Edge(int u = 0, int v = 0, int l = 0, int r = 0, int i = 0): u(u), v(v), l(l), r(r), i(i) {}
  bool operator < (const Edge& e) const {
    if (r == e.r) return i < e.i;
    return r < e.r;
  }
} e[N];

vector<pair<int, int>> adj[N];

int par[N][20], mnr[N][20], mxl[N][20], idx[N], dep[N];
void dfs(int u = 0, int p = -1) {
  for (auto& c : adj[u]) {
    int v, i; tie(v, i) = c;
    if  (v == p) continue;
    par[v][0] = u, idx[v] = i, dep[v] = dep[u] + 1;
    mnr[v][0] = 1e9, mxl[v][0] = e[i].l;
    for (int j = 1; j < 19; ++j) 
      par[v][j] = par[par[v][j - 1]][j - 1], mnr[v][j] = 1e9,
      mxl[v][j] = max(mxl[par[v][j - 1]][j - 1], mxl[v][j - 1]);
    dfs(v, u);
  }
}

void update_r(int u, int v, int w) {
  if (dep[u] <= dep[v]) swap(u, v);
  for (int i = 18; ~i; --i) if (dep[par[u][i]] >= dep[v])
    mnr[u][i] = min(mnr[u][i], w), u = par[u][i];
  if (u == v) return;
  for (int i = 18; ~i; --i) if (par[u][i] != par[v][i])
    mnr[u][i] = min(mnr[u][i], w), u = par[u][i],
    mnr[v][i] = min(mnr[v][i], w), v = par[v][i];
  mnr[u][0] = min(mnr[u][0], w), mnr[v][0] = min(mnr[v][0], w);
}

int get_l(int u, int v) {
  int res = 0;
  if (dep[u] <= dep[v]) swap(u, v);
  for (int i = 18; ~i; --i) if (dep[par[u][i]] >= dep[v])
    res = max(res, mxl[u][i]), u = par[u][i];
  if (u == v) return res;
  for (int i = 18; ~i; --i) if (par[u][i] != par[v][i])
    res = max(res, mxl[u][i]), u = par[u][i],
    res = max(res, mxl[v][i]), v = par[v][i];
  return max(res, max(mxl[u][0], mxl[v][0]));
}

int ans[N];
int n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> n >> m; 
    for (int i = 0; i < n; ++i) adj[i].clear();
    for (int i = 0, u, v, l, r; i < m; ++i) {
      cin >> u >> v >> l >> r, u--, v--;
      e[i] = {u, v, l, r, i};
      if (i < n - 1) 
        adj[u].emplace_back(v, i),
        adj[v].emplace_back(u, i);
    }
    dfs();
    
    for (int i = n - 1; i < m; ++i) {
      e[i].l = max(e[i].l, get_l(e[i].u, e[i].v) + 1);
      update_r(e[i].u, e[i].v, e[i].r - 1);
    }
    
    for (int j = 18; j; --j)
      for (int i = 0; i < n; ++i) 
        mnr[i][j - 1] = min(mnr[i][j - 1], mnr[i][j]),
        mnr[par[i][j - 1]][j - 1] = min(mnr[par[i][j - 1]][j - 1], mnr[i][j]);
        
    for (int i = 1; i < n; ++i)
      e[idx[i]].r = min(e[idx[i]].r, mnr[i][0]);
      
    sort(e, e + m, [](Edge& u, Edge& v) {
      return u.l < v.l;
    });

    set<Edge> s; int flag = 0;
    for (int w = 1, i = 0; w <= m; ++w) {
      while (i < m && e[i].l <= w) s.insert(e[i]), i++;
      if (s.empty() || s.begin()->r < w) {
        cout << "NO\n"; flag = 1; break;
      }
      ans[s.begin()->i] = w; s.erase(s.begin());
    }
    if (flag) continue;
    cout << "YES\n";
    for (int i = 0; i < m; ++i)
      cout << ans[i] << ' ';
    cout << '\n';
  }
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5005;
int x[N], y[N], z[N], p[N];
vector<int> adj[N];
int n, R;

int ans[N], vis[N]; 
int dfs(int u) {
  vis[u] = 1;
  for (int v : adj[u]) if (!~ans[v]) 
    return ans[v] = u, 1;
  for (int v : adj[u]) if (!vis[ans[v]] && dfs(ans[v]))
    return ans[v] = u, 1;
  return 0;
}

int check(int i, int j) {
  if (x[i] == x[j] && y[i] == y[j] && abs(z[i] - z[j]) <= 1) return 1;
  if (x[i] == x[j] && z[i] == z[j] && abs(y[i] - y[j]) <= 1) return 1;
  if (z[i] == z[j] && y[i] == y[j] && abs(x[i] - x[j]) <= 1) return 1;
  return 0;
}

vector<int> vert;
int done[N], sz = 0;
void dfs2(int u, int b = 1) {
  done[u] = 1; sz++;
  if (b) vert.emplace_back(u);
  for (int v : adj[u]) if (!done[v])
    dfs2(v, b^1);
}

int check(ll d) {
  for (int i = 0; i < n; ++i) adj[i].clear();
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) if (check(i, j) && p[i] + p[j] >= d)  
      adj[i].emplace_back(j),
      adj[j].emplace_back(i);
  }
  
  int res = 0;
  memset(ans, -1, sizeof(ans));
  memset(done, 0, sizeof(done));
  for (int i = 0; i < n; ++i) if (!done[i]) {
    vert.clear(); sz = 0; 
    dfs2(i); 
    if (sz == 1) {
      if (p[i] < d) return 0;
      res++; continue;
    }
    int cur = 0;
    for (int u : vert) {
      memset(vis, 0, sizeof(vis));
      cur += dfs(u);
    }
    res += sz - cur;
  }
  return res <= R;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("energy.inp", "r"))
    freopen("energy.inp", "r", stdin),
    freopen("energy.out", "w", stdout);
  cin >> n >> R;
  for (int i = 0; i < n; ++i)
    cin >> x[i] >> y[i] >> z[i] >> p[i];
  ll lo = 0, hi = 1e15, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid)) 
      ans = mid, lo = mid + 1;
    else
      hi = mid - 1;
  }
  cout << ans;
	return 0;
}


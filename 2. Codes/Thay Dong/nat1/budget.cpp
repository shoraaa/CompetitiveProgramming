#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 100 + 5;

int n, m, p;
int a[N], b[N], idx[N][N], id = 0;
vector<int> adj[N];

int match[N * N], vis[N];
int dfs(int u) {
  vis[u] = 1;
  for (int v : adj[u]) if (!~match[v])
    return match[v] = u, 1;
  for (int v : adj[u]) if (!vis[match[v]] && dfs(match[v]))
    return match[v] = u, 1;
  return 0;
}

int check(ll mid) {
  id = 0;
  memset(idx, -1, sizeof(idx));
  for (int i = 0; i < m; ++i) adj[i].clear();
  
  for (int i = 0; i < m; ++i) {
    // voi moi goi kich cau, thu cho no la thang dc an thu k tu phai qua trai cua thang j
    for (int j = 0; j < n; ++j) for (int k = 1; k <= m; ++k) {
      // an thu k -> phan dang sau phai tm mid - b[i] + 1 - a[j] >= a[j] * (k - 1) 
      if (mid - b[i] + 1 - a[j] >= a[j] * ll(k - 1)) {
        if (!~idx[j][k]) idx[j][k] = id++;
        adj[i].emplace_back(idx[j][k]);
      }
    }
  }
  
  int res = 0;
  memset(match, -1, sizeof(match));
  
  for (int i = 0; i < m; ++i) {
    memset(vis, 0, sizeof(vis));
    res += dfs(i);
  }
  
  return res == m;
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> p;
  for (int i = 0; i < n; ++i) 
    cin >> a[i], 
    a[i] = (p + a[i] - 1) / a[i];
  for (int i = 0; i < m; ++i)
    cin >> b[i];
  
  ll lo = 1, hi = 1e12, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid))
      ans = mid, hi = mid - 1;
    else 
      lo = mid + 1;
  }
  cout << ans;
	return 0;
}


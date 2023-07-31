#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 4e5 + 5;
vector<int> adj[N];
int n, m, k;

int color[N], cnt[N], f[N], g[N];

int a[N], b[N]; char c[N];

int vis[N];
int dfs(int u) {
  vis[u] = 1; int cur = 1;
  for (int v : adj[u]) if (!vis[v])
    color[v] = color[u], cur += dfs(v);
  return cur;
}

int check(int mid) {
  for (int i = 1; i <= n; ++i)
    adj[i].clear(), color[i] = -1, cnt[i] = vis[i] = f[i] = g[i] = 0;
  for (int i = 1; i <= mid; ++i) {
    if (c[i] == '=') {
      adj[a[i]].emplace_back(b[i]);
      adj[b[i]].emplace_back(a[i]);
    } else if (c[i] == '<') {
      color[a[i]] = 0, color[b[i]] = 1;
    } else {
      color[a[i]] = 1, color[b[i]] = 0;
    }
  }
  
  int m = k;
  for (int i = 1; i <= n; ++i) if (!vis[i] && ~color[i]) {
    int siz = dfs(i); if (color[i] == 0) m -= siz; 
  } 
  for (int i = 1; i <= n; ++i) if (!vis[i] && !~color[i]) {
    int siz = dfs(i); cnt[siz]++;
  } 

  f[0] = 1;
  for (int j = 1; j <= n; ++j) if (cnt[j]) {
    for (int i = m; i >= m - j + 1; i--) {
      int k = i % j; g[k] = 0;
      for (int p = 1; p < cnt[j] && i - j * p >= 0; ++p) 
        g[k] += f[i - j * p];
    }
    
    for (int i = m; i; i--) {
      int k = i % j;
      if (g[k] > 0) f[i] = 2;
      if (i - cnt[j] * j >= 0) f[i] += f[i - cnt[j] * j], g[k] += f[i - cnt[j] * j];
      if (f[i] > 2) f[i] = 2;
      if (i - j >= 0) g[k] -= f[i - j];
    }
    
    if (f[m] > 1) return 0;
  }

  return f[m] == 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i)
      cin >> a[i] >> c[i] >> b[i];

    int lo = 0, hi = m, mid, ans = -1;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (check(mid))
        ans = mid,
        hi = mid - 1;
      else 
        lo = mid + 1;
    }
    cout << ans << '\n';
  }
	return 0;
}

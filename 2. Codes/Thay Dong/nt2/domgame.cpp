#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005;
string s[N];
vector<int> adj[N * 2];
int n, m;
int idx[N][N];

int x = 0, y = 0;
int vis[N * 2], from[N * 2], to[N * 2];

int dfs(int u) {
  vis[u] = 1;
  for (int v : adj[u]) if (!~to[v])
    return to[v] = u, from[u] = v, 1;
  for (int v : adj[u]) if (!vis[to[v]] && dfs(to[v]))
    return to[v] = u, from[u] = v, 1;
  return 0;
}

void add(int u, int v) {
  adj[u].emplace_back(v);
  adj[v].emplace_back(u);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> s[i];
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (s[i][j] == '#') continue;
    if ((i + j) & 1) idx[i][j] = x++;
    else idx[i][j] = y++;
  }
  
  if (x > 2000) {
    cout << 1000000;
    return 0;
  }
  
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (s[i][j] == '#') continue;
    if ((i + j) & 1) {
      if (i >= 1 && s[i-1][j] != '#') add(idx[i][j], idx[i-1][j] + x);
      if (j >= 1 && s[i][j-1] != '#') add(idx[i][j], idx[i][j-1] + x);
      if (i < n-1 && s[i+1][j] != '#') add(idx[i][j], idx[i+1][j] + x);
      if (j < m-1 && s[i][j+1] != '#') add(idx[i][j], idx[i][j+1] + x);
    }
  }
  
  
  
  memset(to, -1, sizeof(to));
  for (int i = 0; i < x; ++i) {
    memset(vis, 0, sizeof(vis));
    assert(dfs(i));
  }

  ll res = x * (x - 1);
  for (int i = 0; i < x; ++i) {
    queue<int> q; q.emplace(from[i]); 
    memset(vis, 0, sizeof(vis));
    int cnt = 0; vis[from[i]] = 1;
    while (!q.empty()) {
      int v = q.front(); q.pop(); cnt++;
      for (int u : adj[v]) {
        if (!vis[from[u]]) {
          vis[from[u]] = 1;
          q.emplace(from[u]);
        }
      }
    }
    res += y - cnt;
  }

  cout << min(1000000LL, res);
  
  
	return 0;
}

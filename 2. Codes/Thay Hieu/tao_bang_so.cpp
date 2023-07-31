#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = 1e9;
const int N = 500 + 5;
int n, m, s, t;
struct dinic {
  vector<int> adj[N];
  int cap[N][N], flow[N][N];
  int cur[N], level[N];
  
  void add(int u, int v, int c) {
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
    cap[u][v] = c;
  }

  int bfs() {
    memset(level, -1, sizeof(level));
    level[s] = 0;
    queue<int> q;
    q.emplace(s);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : adj[u]) if (!~level[v] && flow[u][v] < cap[u][v])
        level[v] = level[u] + 1, 
        q.emplace(v);
    }
    return ~level[t];
  }
  
  int dfs(int u, int pushed) {
    if (u == t)
      return pushed;
    int flowed = 0;
    for (int v : adj[u]) {
      if (level[u] + 1 != level[v] || flow[u][v] >= cap[u][v]) continue;
      if (int push = dfs(v, min(pushed, cap[u][v] - flow[u][v])))
        flow[u][v] += push,
        flow[v][u] -= push,
        pushed -= push, flowed += push;
      if (pushed == 0)
        return flowed;
    }
    return flowed;
  }
  
  int max_flow() {
    int res = 0;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      res += dfs(s, inf);
    }
    return res;
  }
  
  
  void minimize_flow() {
    for (int r = 1; r <= n; ++r) {
      for (int c = 1; c <= m; ++c) {
        if (flow[r][c + n]) {
          int old_cap = cap[r][c+n], old_revcap = cap[c+n][r];
          cap[r][c+n] = cap[c+n][r] = 0;
          flow[s][r]--, flow[c+n][t]--;
          if (max_flow()) cout << 0;
          else cout << 1, flow[s][r]++, flow[c+n][t]++, cap[r][c+n] = old_cap, cap[c+n][r] = old_revcap;
            
        } else {
          cout << 0, cap[r][c+n] = cap[c+n][r] = 0;
        }
      }
      cout << '\n';
    }
  }
} din;

int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; s = 0, t = n+m+1;
  int row = 0, col = 0;
  for (int r = 1, cap; r <= n; ++r)
    cin >> cap, row += cap, din.add(s, r, cap);
  for (int c = 1, cap; c <= m; ++c)
    cin >> cap, col += cap, din.add(c + n, t, cap);
  if (row != col)
    return cout << -1, 0;
  for (int r = 1; r <= n; ++r)
    for (int c = 1; c <= m; ++c)
      din.add(r, c + n, 1);
  if (din.max_flow() != row)
    return cout << -1, 0;
  din.minimize_flow();
	return 0;
}


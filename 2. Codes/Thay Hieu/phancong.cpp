#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1000 + 5, oo = 1e9;
int rem[N][N], par[N];
vector<int> G[N], T[N];
int n, m, s, t;
struct max_flow {
  int bfs() {
    queue<pair<int, int>> q;
    q.emplace(s, oo);
    memset(par, -1, sizeof(par));
    par[s] = -1;
    while (!q.empty()) {
      int u = q.front().first, f = q.front().second; q.pop();
      if (u == t) 
        return f;
      for (int v : G[u]) if (!~par[v] && rem[u][v])
        par[v] = u, q.emplace(v, min(f, rem[u][v]));
      for (int v : T[u]) if (!~par[v] && rem[u][v])
        par[v] = u, q.emplace(v, min(f, rem[u][v]));
    } 
    return 0;
  }
  int calc() {
    int flow, res = 0;
    while (flow = bfs()) {
      res += flow;
      int u = t;
      while (u != s) {
        int v = par[u];
        rem[v][u] -= flow;
        rem[u][v] += flow;
        u = v;
      }
    }
    return res;
  }
} mf;
int check(int c) {
  for (int u = 1; u <= n; ++u)
    rem[s][u] = c, rem[u][s] = 0;
  for (int u = 1; u <= n; ++u)
    for (int v : G[u]) rem[u][v] = 1, rem[v][u] = 0;
  for (int v = 1; v <= m; ++v)
    rem[n + v][t] = 1;
  return mf.calc() == m;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> m >> n; s = 0, t = n + m + 1;
  for (int u = 1, v; u <= n; ++u) {
    while (cin >> v) {
      if (v == 0) break;
      G[u].emplace_back(n + v),
      T[n + v].emplace_back(u);
    }
  }
  for (int u = 1; u <= n; ++u)
    G[s].emplace_back(u),
    T[u].emplace_back(s);
  for (int v = 1; v <= m; ++v)
    G[v + n].emplace_back(t),
    T[t].emplace_back(n + v);
  int lo = 1, hi = m, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid))
      ans = mid,
      hi = mid - 1;
    else
      lo = mid + 1; 
  }
  if (!~ans) {
    cout << "NO";
  } else {
    cout << "YES\n" << ans << '\n';
    check(ans);
    for (int u = 1; u <= n; ++u) {
      for (int v : G[u]) if (rem[u][v] == 0)
        cout << v - n << ' ';
      cout << 0 << '\n';
    }
    
  }
	return 0;
}


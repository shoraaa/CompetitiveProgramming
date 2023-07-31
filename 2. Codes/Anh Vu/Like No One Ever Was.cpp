#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
const int N = 5e6 + 5, inf = 1e16;
int n, m, s, t;
struct MinCut {
  struct FlowEdge {
    int u, v, c;
    FlowEdge(int u, int v, int c): u(u), v(v), c(c) {}
  };
  vector<FlowEdge> e;
  vector<int> adj[N];
  void add(int u, int v, int c) {
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, c);
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, 0);
  }
  int dis[N], cur[N];
  int bfs() {
    queue<int> q;
    memset(dis, -1, sizeof(dis));
    q.emplace(s);
    dis[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int i : adj[u]) if (!~dis[e[i].v] && e[i].c > 0)
        dis[e[i].v] = dis[u] + 1,
        q.emplace(e[i].v);
    }
    return ~dis[t];
  }
  int dfs(int u, int flow) {
    if (u == t)
      return flow;
    int pushed = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int i = adj[u][cur[u]];
      if (dis[e[i].v] != dis[u] + 1 || e[i].c <= 0) continue;
      if (int push = dfs(e[i].v, min(flow, e[i].c)))
        e[i].c -= push, e[i^1].c += push,
        flow -= push, pushed += push;
      if (flow == 0) break;
    }
    return pushed;
  }
  int calculate() {
    int res = 0;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      res += dfs(s, inf);
    }
    return res;
  }
} min_cut;
int v[N], c[N], lp[N];
vector<pair<int, int>> fac[N];
int id = 0;
signed main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> v[i];
  for (int i = 1; i <= n; ++i)
    cin >> c[i];
  for (int i = 2; i <= n; ++i) if (!lp[i]) 
	  for (int j = i; j <= n; j += i) lp[j] = i;
    
  s = id++, t = id++;
  map<pair<int, int>, int> mp;
  for (int i = 2; i <= n; ++i) if (lp[i] == i) {
    ll x = 1;
    for (int j = 1;; ++j) {
      x *= i; if (x > n) break;
      min_cut.add(id, t, c[i] * (2*j - 1));
      mp[{i, j}] = id++;
    }
  }
  ll sum = 0;
  for (int i = 1; i <= n; ++i) {
    min_cut.add(s, id, v[i]); sum += v[i];
    int val = i;
    while (val > 1) {
      int x = lp[val], cnt = 0;
      while (val % x == 0)
        val /= x, cnt++;
      for (int j = 1; j <= cnt; ++j)
        min_cut.add(id, mp[{x, j}], inf);
    }
    id++;
  }
  cout << sum - min_cut.calculate();
	return 0;
}


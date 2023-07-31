#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
const ll llinf = 1e18;
int n, m, s, t, sum = 0;
struct dinic {
  struct edge {
    int u, v; ll flow, cap;
    edge(int u, int v, ll c): u(u), v(v), cap(c), flow(0) {}
  };
  vector<edge> edges;
  vector<int> adj[N];
  int cur[N], level[N];
  ll lwb;
  void add(int u, int v, ll c) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(u, v, c);
    adj[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0);
  }
  void reset() {
    for (int u = s; u <= t; ++u)   
      adj[u].clear();
    edges.clear();
  }
  int bfs() {
    queue<int> q;
    q.emplace(s);
    memset(level, -1, sizeof(level));
    level[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int id : adj[u]) if (!~level[edges[id].v] && edges[id].cap - edges[id].flow >= lwb)
        level[edges[id].v] = level[u] + 1, 
        q.emplace(edges[id].v);
    }
    return ~level[t];
  }
  ll dfs(int u, ll pushed) {
    if (u == t)
      return pushed;
    ll sum = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int id = adj[u][cur[u]], v = edges[id].v, push; 
      ll cap = edges[id].cap, flow = edges[id].flow;
      if (cap - flow < lwb || level[u] + 1 != level[v]) continue;
      if (push = dfs(v, min(pushed - sum, cap - flow))) {
        edges[id].flow += push, 
        edges[id ^ 1].flow -= push;
        sum += push;
        if (sum == pushed)
          return sum;
      }
    }
    return sum;
  }
  ll max_flow() {
    ll flow = 0; lwb = 1;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      while (ll push = dfs(s, llinf))
        flow += push;
    }
    return flow;
  }
} din;

struct S {
  int val, cnt, idx;
  S(int val, int cnt, int idx): val(val), cnt(cnt), idx(idx) {}
};
vector<S> facto[N];
int id = 1;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m, s = 0, t = N-1;
  for (int i = 1, x; i <= n; ++i) {
    cin >> x; 
    for (int d = 2; d * d <= x; ++d) if (x % d == 0) {
      int cnt = 0;
      while (x % d == 0) x /= d, cnt++;
      facto[i].emplace_back(d, cnt, id++);
    }
    if (x > 1) facto[i].emplace_back(x, 1, id++);
     
    if (i & 1) {
      for (auto& p : facto[i])
        din.add(s, p.idx, p.cnt);
    } else {
      for (auto& p : facto[i])
        din.add(p.idx, t, p.cnt);
    }
    
  }
  for (int i = 0, u, v; i < m; ++i) {
    cin >> u >> v; if (u % 2 == 0) swap(u, v); // u le v chan
    for (auto& p1 : facto[u]) for (auto& p2 : facto[v]) 
      if (p1.val == p2.val) din.add(p1.idx, p2.idx, llinf);
  }
  cout << din.max_flow();
	return 0;
}


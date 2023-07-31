#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 5;
const ll oo = 1e18;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
int n = 1, s, t;
int vis[N];
struct dinic {
  struct edge {
    int u, v, id; ll cap;
    edge(int u, int v, int id, int c): u(u), v(v), id(id), cap(c) {}
  };
  vector<edge> edges;
  vector<int> adj[N];
  int cur[N], level[N];
  ll lwb;
  void add(int u, int v, int id) {
    adj[u].emplace_back(edges.size());
    edges.emplace_back(u, v, id, 1);
    adj[v].emplace_back(edges.size());
    edges.emplace_back(v, u, id, 0);
  }
  int bfs() {
    queue<int> q;
    q.emplace(s);
    memset(level, -1, sizeof(level));
    level[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int id : adj[u]) if (!~level[edges[id].v] && edges[id].cap >= lwb)
        level[edges[id].v] = level[u] + 1, 
        q.emplace(edges[id].v);
    }
    return ~level[t];
  }
  ll dfs(int u, ll pushed) {
    if (pushed == 0)
      return 0;
    if (u == t)
      return pushed;
    int ans = 0;
    for (; cur[u] < adj[u].size(); ++cur[u]) {
      int id = adj[u][cur[u]], v = edges[id].v, push; ll cap = edges[id].cap;
      if (cap < lwb || level[u] + 1 != level[v]) continue;
      if (push = dfs(v, min(pushed, cap))) {
        edges[id].cap -= push, 
        edges[id ^ 1].cap += push;
        return push;
      }
    }
    return 0;
  }
  ll max_flow(ll b) {
    ll res = 0; lwb = b;
    while (bfs()) {
      memset(cur, 0, sizeof(cur));
      while (int push = dfs(s, oo))
        res += push;
    }
    cout << res << '\n';
    vis[s] = vis[t] = 1;
    for (int idt : adj[t]) if (~level[edges[idt].v]) {
      vector<int> seq; 
      for (int idv : adj[edges[idt].v]) if (!vis[edges[idv].id])
        seq.emplace_back(edges[idv].id), vis[edges[idv].id] = 1;
      cout << seq.size() << ' ';
      for (int u : seq) cout << u << ' ';
      cout << '\n';
    }
    for (int ids : adj[s]) if (!~level[edges[ids].v]) {
      vector<int> seq; 
      for (int idv : adj[edges[ids].v]) if (!vis[edges[idv].id])
        seq.emplace_back(edges[idv].id), vis[edges[idv].id] = 1;
      if (seq.empty()) continue;
      cout << seq.size() << ' ';
      for (int u : seq) cout << u << ' ';
      cout << '\n';
    }
  }
} din;
int m, k;
map<string, int> idp, ids;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int q, k; cin >> q >> k; s = 0, t = q*2+5;
  din.edges.reserve(n * n);
  string str, prefix, suffix;
  for (int i = 1; i <= q; ++i) {
    cin >> str; 
    prefix = str.substr(0, k), suffix = str.substr(str.size() - k, k);
    if (!idp.count(prefix)) 
      idp[prefix] = n++,
      din.add(s, idp[prefix], 0);
    if (!ids.count(suffix))
      ids[suffix] = n++,
      din.add(ids[suffix], t, 0);
    din.add(idp[prefix], ids[suffix], i);
  }
  din.max_flow(1);
	return 0;
}


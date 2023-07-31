#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll llinf = 1e18;
const int inf = 2e9;
const int N = 2e5 + 5;
void file() {
	const string FILE_NAME = "hotel";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int n, k, s, t;
struct query {
  int l, r, v, i;
  query(int l, int r, int v, int i): l(l), r(r), v(v) {}
};
vector<query> que;
vector<int> tl; 
int in[N], out[N];
struct dinic {
  struct edge {
    int u, v, c, w, f;
    edge(int u, int v, int w, int c): u(u), v(v), w(w), c(c), f(0) {}
  };
  vector<edge> e;
  vector<int> adj[N];
  int add(int u, int v, int w, int c) {
    int i = e.size();
    adj[u].emplace_back(e.size());
    e.emplace_back(u, v, w, c);
    
    adj[v].emplace_back(e.size());
    e.emplace_back(v, u, -w, 0);
    return i;
  }
  ll cost = 0;
  ll dis[N];
  int inq[N], cur[N], par[N];
  int bfs() {
    queue<int> q;
    fill(begin(dis), end(dis), -llinf);
    memset(inq, 0, sizeof(inq));
    q.emplace(s);
    dis[s] = 0; inq[s] = 1;
    while (!q.empty()) {
      int u = q.front(); q.pop(); inq[u] = 0;
      for (int i : adj[u]) if (e[i].c - e[i].f > 0 && dis[u] + e[i].w > dis[e[i].v]) {
        dis[e[i].v] = dis[u] + e[i].w;
        par[e[i].v] = i;
        if (!inq[e[i].v])
          q.emplace(e[i].v), inq[e[i].v] = 1;
      }
    }
    if (dis[t] <= 0)
      return 0;
    int u = t;
    while (u != s) {
      int i = par[u], v = e[i].u;
      e[i].f += 1, e[i^1].f -= 1, cost += e[i].w;
      u = v;
    }
    return 1;
  }
  void min_cost() {
    while (bfs()) {}
    // for (int i = 0; i < e.size(); i += 2) {
      // auto ed = e[i];
      // cerr << ed.u << ' ' << ed.v << ' ' << ed.w << ',' << ed.f << '/' << ed.c << '\n';
    // }
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
      auto q = que[i];
      int l = lower_bound(tl.begin(), tl.end(), q.l) - tl.begin(),
          r = lower_bound(tl.begin(), tl.end(), q.r) - tl.begin() + 1;
      for (int id : adj[out[l]]) if (id == q.i) {
        ans[i] = e[id].f == e[id].c; break;
      }
    }
    cout << cost << '\n';
    for (int v : ans)
      cout << v << ' ';
  }
} din;
int id = 0;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
  cin >> n >> k; s = id++;
  for (int i = 0, l, r, v; i < n; ++i) {
    cin >> l >> r >> v; r = l + r - 1;
    tl.emplace_back(l), tl.emplace_back(r);
    que.emplace_back(l, r, v, i);
  }
  sort(tl.begin(), tl.end()); tl.emplace_back(inf);
  tl.erase(unique(tl.begin(), tl.end()), tl.end());
  for (int i = 0; i < tl.size(); ++i)
    in[i] = id++, out[i] = id++,
    din.add(in[i], out[i], 0, k);
  t = id++;
  din.add(s, in[0], 0, inf);
  din.add(out[tl.size()-1], t, 0, inf);
  for (int i = 0; i < tl.size() - 1; ++i)
    din.add(out[i], in[i+1], 0, inf);
  for (auto& q : que) {
    int l = lower_bound(tl.begin(), tl.end(), q.l) - tl.begin(),
        r = lower_bound(tl.begin(), tl.end(), q.r) - tl.begin() + 1;
    q.i = din.add(out[l], in[r], q.v, 1);
  }
  din.min_cost();
	return 0;
}
                                                              
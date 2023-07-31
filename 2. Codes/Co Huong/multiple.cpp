#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int C = 3e6 + 5, K = 20;
struct Trie {
  int nxt[C][10], par[C][K], dep[C], val[C];
  int id;
  Trie(): id(1) {}
  int cmp(int u, int v) {
    if (u == -1) return 0;
    if (v == -1) return 1;
    if (dep[u] != dep[v]) return dep[u] < dep[v];
    for (int k = K-1; ~k; --k) if (par[u][k] != par[v][k])
      u = par[u][k], v = par[v][k];
    return val[u] < val[v];
  }
  void emplace(int u, int p) {
    memset(nxt[u], 0, sizeof(nxt[u]));
    par[u][0] = p; dep[u] = dep[p] + 1;
    for (int i = 1; i < K; ++i)
      par[u][i] = par[par[u][i-1]][i-1];
  }
  int insert(int u, int d) {
    if (!nxt[u][d])
      nxt[u][d] = id, emplace(id, u), 
      val[id] = d, id++;
    u = nxt[u][d]; 
    return u;
  }
} trie;
struct State {
  int m, d;
  State(int m, int d): m(m), d(d) {}
  bool operator < (const State& s) const {
    return !trie.cmp(d, s.d);
  }
};
const int N = 1e4 + 5, inf = 1e9;
int del[10], dis[N], to[N];
int n, k;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("multiple.in", "r"))
    freopen("multiple.in", "r", stdin),
    freopen("multiple.out", "w", stdout);
  cin >> n >> k;
  for (int i = 0, x; i < k; ++i)
    cin >> x, del[x] = 1;
  vector<int> num;
  for (int i = 0; i < 10; ++i)
    if (!del[i]) num.emplace_back(i);
  priority_queue<State> q;
  fill(begin(dis), end(dis), -1);
  for (int d : num) if (d > 0 && !~dis[d % n])
    dis[d % n] = trie.insert(0, d), 
    to[d % n] = -1,
    q.emplace(d % n, dis[d % n]);
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    if (s.d != dis[s.m]) continue;
    if (s.m == 0) {
      string t;
      for (int i = s.m; ~i; i = to[i])
        t += char(trie.val[dis[i]] + '0');
      reverse(t.begin(), t.end());
      if (t.size() < 9) return cout << t, 0;
      int m = t.size() - 1;
      return cout << t[0] << t[1] << t[2] << "..."
                  << t[m] << t[m-1] << t[m-2] << '(' << m+1 << " digits)", 0;
    }
    for (int d : num) {
      int nm = (s.m * 10 + d) % n, nv;
      if (trie.cmp(nv = trie.insert(s.d, d), dis[nm]))
        dis[nm] = nv, to[nm] = s.m, q.emplace(nm, dis[nm]);
    }
  }
  return cout << "IMPOSSIBLE", 0;
}


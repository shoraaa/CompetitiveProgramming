#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
const int C = 1e6 + 5, K = 20;
struct Trie {
  int nxt[C][26], par[C][K], dep[C], val[C];
  int id;
  Trie(): id(1) {}
  int cmp(int u, int v) {
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
  int insert(int u, int c) {
    if (!nxt[u][c])
      nxt[u][c] = id, emplace(id, u), 
      val[id] = c, id++;
    u = nxt[u][c];
    return u;
  }
} trie;
string s;
struct State {
  int i, d, v;
  State(int i, int d, int v): i(i), d(d), v(v) {}
  bool operator < (const State& s) const {
    if (d != s.d) return d > s.d;
    return !trie.cmp(v, s.v);
  }
};
int vis[26], dis[N], nxt[N][26];
pair<int, char> to[N];
int n;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> s; n = s.size(); s = ' ' + s;
  for (int c = 0; c < 26; ++c)
    nxt[n][c] = n + 1;
  for (int i = n-1; ~i; --i)
    for (int c = 0; c < 26; ++c)
      if (c == s[i + 1] - 'a') nxt[i][c] = i + 1;
      else nxt[i][c] = nxt[i + 1][c];
  priority_queue<State> q;
  memset(dis, -1, sizeof(dis));
  q.emplace(0, 0, 0); dis[0] = 0;
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    for (int c = 0; c < 26; ++c) if (!~dis[nxt[s.i][c]]) 
      dis[nxt[s.i][c]] = s.d + 1, to[nxt[s.i][c]] = {s.i, c + 'a'},
      q.emplace(nxt[s.i][c], s.d + 1, trie.insert(s.v, c));
  }
  string res;
  for (int i = n + 1; i; i = to[i].first)
    res += to[i].second;
  reverse(res.begin(), res.end());
  cout << res;
	return 0;
}


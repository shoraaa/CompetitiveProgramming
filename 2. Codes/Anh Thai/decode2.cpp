#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005;
bitset<N> vis[2][N];
struct Trace {
  int u, v, t, type = 0; char c;
  Trace(int u=0, int v=0, int t=0, char c=0, int type=0): u(u), v(v), t(t), c(c), type(type) {}
} tr[N][N][2];

struct Trie {
  struct Node {
    int nxt[26], leaf;
    Node(): leaf(0) {
      memset(nxt, 0, sizeof(nxt));
    }
  };
  vector<Node> trie;
  Trie(): trie(1) {}
  #define nxt(u, c) trie[u].nxt[c - 'a']
  #define leaf(u) trie[u].leaf
  void add(const string& s) {
    int u = 0;
    for (char c : s) {
      if (!nxt(u, c))
        nxt(u, c) = trie.size(),
        trie.emplace_back();
      u = nxt(u, c);
    }
    leaf(u) = 1;
  }
  #define fi first
  #define se second
  void solve() {
    int n = trie.size();
    queue<tuple<int, int, int>> q;
    vis[0][0][0] = 1;
    q.emplace(0, 0, 0);
    string a, b;
    while (!q.empty()) {
      int u, v, t; tie(u, v, t) = q.front(); q.pop();
      if (leaf(u) && leaf(v) && t) {
        for (;;) {
          a += tr[u][v][t].c; b += tr[u][v][t].c;
          if (tr[u][v][t].type == 1) a += '+';
          else if (tr[u][v][t].type == 2) b += '+';
          int pu = tr[u][v][t].u, pv = tr[u][v][t].v, pt = tr[u][v][t].t;
          u = pu, v = pv, t = pt;
          if (u == 0 && v == 0 && t == 0) break;
        }
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        cout << a << '\n' << b << '\n';
        return;
      }
      for (char    ++c) {
        if (!nxt(u, c) || !nxt(v, c)) continue;
        if (vis[t][nxt(u, c)][nxt(v, c)]) continue;
        vis[t][nxt(u, c)][nxt(v, c)] = 1;
        tr[nxt(u, c)][nxt(v, c)][t] = Trace(u, v, t, c);
        q.emplace(nxt(u, c), nxt(v, c), t);
      }
      if (leaf(u)) {
        for (char c = 'a'; c <= 'z'; ++c) {
          if (!nxt(0, c) || !nxt(v, c)) continue;
          if (vis[1][nxt(0, c)][nxt(v, c)]) continue;
          vis[1][nxt(0, c)][nxt(v, c)] = 1;
          tr[nxt(0, c)][nxt(v, c)][1] = Trace(u, v, t, c, 1);
          q.emplace(nxt(0, c), nxt(v, c), 1);
        }
      }
      if (leaf(v)) {
        for (char c = 'a'; c <= 'z'; ++c) {
          if (!nxt(u, c) || !nxt(0, c)) continue;
          if (vis[1][nxt(u, c)][nxt(0, c)]) continue;
          vis[1][nxt(u, c)][nxt(0, c)] = 1;
          tr[nxt(u, c)][nxt(0, c)][1] = Trace(u, v, t, c, 2);
          q.emplace(nxt(u, c), nxt(0, c), 1);
        }
      }
    }
    cout << -1;
  }
} trie;

int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; string s;
  for (int i = 0; i < n; ++i)
    cin >> s, trie.add(s);
  trie.solve();
	return 0;
}


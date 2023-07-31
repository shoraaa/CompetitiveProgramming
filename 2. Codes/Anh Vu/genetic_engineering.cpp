#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int M = 1e9 + 9;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
int dict[256]; string alphabet = "ACGT";
struct PrefixTree {
  struct Node {
    int link, leaf, dep, nxt[4];
    Node(): link(0), dep(0), leaf(0) {
      memset(nxt, 0, sizeof(nxt));
    }
  };
  vector<Node> pt;
  PrefixTree(): pt(1) {}
  int size() {
    return pt.size();
  }
  int& nxt(int u, int c) {
    return pt[u].nxt[c];
  }
  int& link(int u) {
    return pt[u].link;
  }
  int& leaf(int u) {
    return pt[u].leaf;
  }
  int& dep(int u) {
    return pt[u].dep;
  }
  void add(string& s) {
    int u = 0;
    for (char c : s) {
      if (!nxt(u, dict[c]))
        nxt(u, dict[c]) = pt.size(),
        pt.emplace_back();
      u = nxt(u, dict[c]);
    }
    leaf(u) = u;
  }
  void bfs() {
    queue<int> q;
    q.emplace(0);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (!leaf(u)) leaf(u) = leaf(link(u));
      for (int c = 0; c < 4; ++c) {
        int v = nxt(u, c);
        if (v)
          link(v) = u ? nxt(link(u), c) : 0, dep(v) = dep(u) + 1, q.emplace(v);
        else nxt(u, c) = nxt(link(u), c);
      }
    }
  }
} pt;
const int N = 1000 + 5;
int dp[2][N][10 * 10 * 4 + 5];
int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  for (int i = 0; i < 4; ++i)
    dict[alphabet[i]] = i;
  cin >> n >> m;
  string s;
  for (int i = 0; i < m; ++i) {
    cin >> s;
    if (s.size() > n) continue;
    pt.add(s);
  }
  pt.bfs();
  dp[0][0][0] = 1;
  for (int i = 0; i < n; ++i) {
    int cur = i & 1, nxt = cur ^ 1;
    memset(dp[nxt], 0, sizeof(dp[nxt]));
    for (int j = 0; j <= i; ++j) for (int u = 0; u < pt.size(); ++u) {
      if (!dp[cur][j][u]) continue;
      for (int c = 0; c < 4; ++c) if (pt.nxt(u, c)) {
        int nu = pt.nxt(u, c), nj = j+1;
        if (pt.leaf(nu) && pt.dep(pt.leaf(nu)) >= j+1) nj = 0;
        add(dp[nxt][nj][nu], dp[cur][j][u]);
      }
    }
  }
  int res = 0;
  for (int u = 1; u < pt.size(); ++u)
    if (pt.leaf(u)) add(res, dp[n & 1][0][u]);
  cout << res;
	return 0;
}


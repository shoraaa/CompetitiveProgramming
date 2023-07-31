#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct Trie {
  struct Node {
    int nxt[26], leaf = 0;
    Node() { memset(nxt, -1, sizeof(nxt)); }
  };
  vector<Node> trie; int r, ans;
  Trie(): trie(1), r(0), ans(0) {}
  void append_front(int c) {
    int old = r; ans++;
    r = trie.size();
    trie.emplace_back();
    trie.back().nxt[c] = old;
    trie[old].leaf = 1;
  }
  int size() { return trie.size(); }
  Node& operator [] (int v) { return trie[v]; } 
  void merge(Trie& other, int u, int v) {
    if (!trie[u].leaf && other[v].leaf)
      trie[u].leaf = 1, ans++;
    for (int c = 0; c < 26; ++c) if (~other[v].nxt[c]) {
      if (!~trie[u].nxt[c]) 
        trie[u].nxt[c] = trie.size(),
        trie.emplace_back();
      merge(other, trie[u].nxt[c], other[v].nxt[c]);
    }
  } 
};
const int N = 3e5 + 5;
int a[N], ans[N];
vector<int> adj[N];
string s;
int n;
Trie dfs(int u, int p = -1) {
  Trie cur; cur.append_front(s[u] - 'a');
  for (int v : adj[u]) if (v != p) {
    Trie nxt = dfs(v, u); nxt.append_front(s[u] - 'a');
    if (cur.size() < nxt.size()) swap(cur, nxt);
    cur.merge(nxt, cur.r, nxt.r);
  }
  ans[u] = cur.ans;
  return cur;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int v = 0; v < n; ++v)
    cin >> a[v];
  cin >> s;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  dfs(0); pair<int, int> res = {0, 0};
  for (int v = 0; v < n; ++v)
    if (res.first < ans[v] + a[v]) 
      res = {ans[v] + a[v], 1};
    else if (res.first == ans[v] + a[v])
      res.second += 1;
  cout << res.first << '\n' << res.second;
	return 0;
}


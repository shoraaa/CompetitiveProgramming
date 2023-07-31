#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int n, l, k, m;

struct TrieNode {
  int nxt[26], id = 0;
  TrieNode() {
    memset(nxt, 0, sizeof(nxt));
  }
};
vector<TrieNode> trie;

#define nxt(u, c) trie[u].nxt[c - 'a']

int id = 0;
string str[N];
int get(const string& s) {
  int u = 0;
  for (char c : s) {
    if (!nxt(u, c)) {
      nxt(u, c) = trie.size();
      trie.emplace_back();
    }
    u = nxt(u, c);
  }
  if (!trie[u].id) {
    trie[u].id = ++id;
    str[id] = s;
  }
  return trie[u].id;
}

int ok[N], deg[N];
vector<int> adj[N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> l >> k >> m;
  string s, t;
  queue<int> q;
  
  trie.emplace_back();
  
  for (int i = 1; i <= k; ++i) {
    cin >> s;
    int u = get(s);
    ok[u] = 1;
    q.emplace(u);
  }
  
  for (int i = 1; i <= m; ++i) {
    cin >> s >> t;
    int u = get(s), v = get(t);
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  
  for (int i = 1; i <= id; ++i) {
    sort(adj[i].begin(), adj[i].end());
    adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
  }
  
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) if (!ok[v]) {
      deg[v]++;
      if (deg[v] >= l) {
        ok[v] = 1;
        q.emplace(v);
      }
    }
  }
  
  vector<string> ans;
  for (int i = 1; i <= id; ++i) {
    if (!ok[i]) continue;
    ans.emplace_back(str[i]);
  }
  
  cout << ans.size() << '\n';
  sort(ans.begin(), ans.end());
  for (string& s : ans) {
    cout << s << ' ';
  }
  
	return 0;
}

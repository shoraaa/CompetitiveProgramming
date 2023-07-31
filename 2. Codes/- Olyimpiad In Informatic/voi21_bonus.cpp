#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 5;

struct Node {
  int nxt[26];
  ll val = 0;
  Node() {
    memset(nxt, 0, sizeof(nxt));
  }
}; 
vector<Node> trie;

#define nxt(u, c) trie[u].nxt[c - 'A']

void update(const string& s, ll val) {
  int u = 0; 
  
  for (char c : s) {
    trie[u].val = max(trie[u].val, val);
    if (!nxt(u, c)) {
      nxt(u, c) = trie.size();
      trie.emplace_back();
    }
    u = nxt(u, c);
  }
  
}

ll get(const string& s) {
  int u = 0;
  for (char c : s) {
    if (!nxt(u, c)) {
      return 0;
    }
    u = nxt(u, c);
  }
  return trie[u].val;
}

string s[N];
int a[N];
int n, m;

int big[N];
vector<int> adj[N], adj_big[N];

ll f[N], g[N];


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  
  int lim = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> s[i] >> a[i];
    lim = max(lim, a[i]);
  }
  
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  
  int K = sqrt(m * 2);
  
  for (int i = 1; i <= lim; ++i) {
    if (adj[i].size() > K) {
      big[i] = 1;
      
      for (int v : adj[i]) {
        adj_big[v].emplace_back(i);
      }
      
    }
  }
  
  // root
  trie.emplace_back();
  trie.reserve(1 << 20);
  
  ll res = 0;
  
  for (int i = 1; i <= n; ++i) {
    
    int u = a[i];
    
    // f[x] = max dp cua nhung thang ke x (maybe incorrent cuz x not visited)
    // g[x] = max dp cua x (only for big boi) (always correct)
    
    for (int v : adj_big[u]) {
      f[u] = max(f[u], g[v]);
    }
    
    ll dpi = max(f[u], get(s[i])) + a[i];
    
    update(s[i], dpi);
    res = max(res, dpi);
    
    if (!big[u]) {
      
      for (int v : adj[u]) {
        f[v] = max(f[v], dpi);
      }
      
    } else {
      
      g[u] = max(g[u], dpi);
      
    }
    
    
  }
  
  cout << res;
  
	return 0;
}

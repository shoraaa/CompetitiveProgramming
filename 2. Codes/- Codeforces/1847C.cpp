#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int n;

struct Trie {
  struct Node {
    int nxt[2];
    Node() {
      nxt[0] = nxt[1] = 0;
    }
  };
  vector<Node> trie;
  Trie(): trie(1) {}
  
  #define bit(x, i) !!(x & (1 << i))
  #define nxt(u, b) trie[u].nxt[b]
  
  void insert(int x) {
    int u = 0;
    for (int i = 7; ~i; --i) {
      int b = bit(x, i);
      if (!nxt(u, b)) {
        nxt(u, b) = trie.size();
        trie.emplace_back();
      }
      u = nxt(u, b);
    }
  }
  
  int get(int x) {
    int u = 0, res = 0;
    for (int i = 7; ~i; --i) {
      int b = bit(x, i);
      
      if (nxt(u, b^1)) u = nxt(u, b^1), res ^= 1 << i;
      else u = nxt(u, b);
    }
    return res;
  }
} trie;


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    
    trie = Trie();
    trie.insert(0);
    
    int val = 0, res = -1e9;
    for (int i = 1, x; i <= n; ++i) {
      cin >> x;
      val ^= x;
      trie.insert(val);
      res = max(res, trie.get(val));
    }
    cout << res << '\n';
  }

	return 0;
}


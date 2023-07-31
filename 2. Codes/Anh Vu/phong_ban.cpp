#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;
struct DSU {
  int par[N];
  void reset(int n) {
    for (int i = 1; i <= n; ++i) par[i] = i;
  }
  int find(int u) {
    if (u == par[u]) return u;
    return par[u] = find(par[u]);
  }
  void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    par[u] = v;
  }
} dsu1, dsu2;
  
int n, q;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q; dsu1.reset(n); dsu2.reset(n);
  for (int i = 0, t, l, r; i < q; ++i) {
    cin >> t >> l >> r;
    if (t == 1) dsu1.unite(l, r);
    else if (t == 2) {
      int root = dsu2.find(r);
      for (int i = dsu2.find(l); i < r; i = dsu2.find(i + 1)) 
        dsu1.unite(i, root), dsu2.unite(i, root);
      
    } else {
      cout << (dsu1.find(l) == dsu1.find(r) ? "YES\n" : "NO\n");
    }
  }

	return 0;
}


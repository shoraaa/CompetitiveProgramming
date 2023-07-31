#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5, inf = 1e9;
vector<int> adj[N];
int a[N];
int n;
multiset<int> dfs(int u = 0, int p = -1) {
  multiset<int> seq;
  for (int v : adj[u]) if (v != p) {
    auto nxt = dfs(v, u);
    if (nxt.size() > seq.size()) swap(nxt, seq);
    for (int val : nxt)
      seq.insert(val);
  }
  seq.insert(a[u]);
  auto it = seq.lower_bound(a[u]); it++;
  if (it != seq.end()) seq.erase(it);
  return seq;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; int root;
  for (int u = 0, v, p; u < n; ++u) {
    cin >> v >> p, p--;
    if (p != -1)
      adj[p].emplace_back(u),
      adj[u].emplace_back(p);
    else
      root = u;
    a[u] = v;
  }
  cout << dfs().size();
	return 0;
}


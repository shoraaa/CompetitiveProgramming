#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5, M = 1e9 + 7;
int mul(ll x, ll y) { return x * y % M; }
int dif(int x, int y) { x -= y; if (x < 0) x += M; return x; }
int pw(int x, int k) {
  int res = 1;
  for (; k; k >>= 1, x = mul(x, x))
    if (k & 1) res = mul(res, x);
  return res;
}
vector<int> adj[N], layer[N];
int dep[N], vis[N];
int n, m;
int solve() {
  int res = 1;
  for (int d = 1; d <= n; ++d) {
    int prev = 0;
    for (int u : layer[d]) {
      if (layer[d - 1].empty()) return 0;
      int cnt0 = 0, cnt1 = prev;
      for (int v : adj[u]) 
        if (dep[v] == d - 1) cnt0++;
        else if (dep[v] == d && vis[v]) cnt1--;
        else if (dep[v] > d + 1) return 0;
      if (cnt0) res = mul(res, pw(2, layer[d - 1].size() - cnt0));
      else res = mul(res, dif(pw(2, layer[d - 1].size()), 1));
      res = mul(res, pw(2, cnt1)); 
      prev++; vis[u] = 1;
    }
  } 
  return res;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; layer[0].emplace_back(0);
  for (int i = 1; i < n; ++i) {
    cin >> dep[i], layer[dep[i]].emplace_back(i);
    if (dep[i] == 0) return cout << 0, 0;
  }
  for (int i = 0, u, v; i < m; ++i) {
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
    if (abs(dep[u] - dep[v]) > 1)
      return cout << 0, 0;
  }
  cout << solve();
	return 0;
}


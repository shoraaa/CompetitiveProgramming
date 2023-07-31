#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5, inf = 1e9;
struct Adjacent {
  int v, d;
  Adjacent(int v, int d): v(v), d(d) {}
  bool operator == (const Adjacent& c) const {
    return v == c.v && d == c.d;
  }
  bool operator < (const Adjacent& c) const {
    return d < c.d;
  }
};
vector<Adjacent> adj[N];
int s[N], ans[N];
int n, k;
int get(int l, int r) {
  l = lower_bound(s, s + k, l) - s;
  r = upper_bound(s, s + k, r) - s - 1;
  return max(0, r - l + 1);
}
void dfs(int u, int l = 1, int r = inf) {
  if (l > r) return; ans[u] = get(l, r); 
  sort(adj[u].begin(), adj[u].end());
  for (int i = 0; i < adj[u].size(); ++i) {
    auto c = adj[u][i];
    int m = min(c.v == adj[u].back().v ? r : (c.d + adj[u][i+1].d) / 2, r);
    adj[c.v].erase(find(adj[c.v].begin(), adj[c.v].end(), Adjacent(u, c.d)));
    dfs(c.v, l, m); l = max(l, m + 1);
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0, u, v, d; i < n-1; ++i)
    cin >> u >> v >> d, u--, v--,
    adj[u].emplace_back(v, d),
    adj[v].emplace_back(u, d);
  for (int i = 0; i < k; ++i)
    cin >> s[i];
  sort(s, s + k);
  dfs(0);
  for (int v = 0; v < n; ++v)
    cout << ans[v] << " \n"[v == n-1];
	return 0;
}


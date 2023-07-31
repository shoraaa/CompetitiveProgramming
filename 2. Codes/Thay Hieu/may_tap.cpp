#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e3 + 5;
const ll oo = 1e18;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
int vis[N], W, H;
vector<pair<int, int>> a;
vector<int> G[N];
vector<int> lside;
int match[N];
int n, m;
void dfs(int u, int b) {
  if (!b) lside.emplace_back(u);
  for (int v : G[u]) if (!vis[v]) 
    vis[v] = 1, dfs(v, !b);
}
int matching(int u) {
  if (vis[u]) return 0;
  vis[u] = 1;
  for (int v : G[u]) if (!~match[v])
    return match[v] = u, 1;
  for (int v : G[u]) if (matching(match[v]))
    return match[v] = u, 1;
  return 0;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> W >> H; 
  a.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i].first >> a[i].second;
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  n = a.size();
  for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j)
    if (abs(a[i].first - a[j].first) + abs(a[i].second - a[j].second) == 1)
      G[i].emplace_back(j), G[j].emplace_back(i); 
  for (int u = 0; u < n; ++u) if (!vis[u])
    vis[u] = 1, dfs(u, 0);
  int max_matching = 0;
  vector<int> order = lside;
  shuffle(order.begin(), order.end(), rng);
  memset(match, -1, sizeof(match));
  for (int u : order) {
    memset(vis, 0, sizeof(vis));
    max_matching += matching(u);
  }
  cout << n - max_matching;
	return 0;
}


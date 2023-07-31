#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
vector<int> adj[N];
int icl[N], vis[N], ind[N];
int n = 0;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int t, k;
  cin >> t;
  while (t--) {
    cin >> k;
    vector<int> a(k);
    for (int i = 0; i < k; ++i)
      cin >> a[i], icl[a[i]] = 1, n = max(n, a[i]);
    for (int i = 0; i < k-1; ++i)
      adj[a[i]].emplace_back(a[i+1]),
      ind[a[i+1]]++;
  }
  priority_queue<pair<int, int>> q;
  for (int u = 1; u <= n; ++u) if (icl[u] && !ind[u])
    q.emplace(0, -u);
  vector<int> ans;
  while (!q.empty()) {
    auto u = -q.top().second; q.pop();
    if (vis[u]) continue;
    ans.emplace_back(u), vis[u] = 1;
    for (int v : adj[u]) 
      ind[v]--, q.emplace(-ind[v], -v);
  }
  for (int i = 0; i < ans.size(); ++i)
    cout << ans[i] << ' ';
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
vector<int> adj[N];
int n;

int siz[N], cnt[N];
void dfs(int u = 0, int p = -1) {
  siz[u] = 1;
  for (int v : adj[u]) if (v != p)
    dfs(v, u), siz[u] += siz[v];
  cnt[siz[u]]++;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  dfs(0);
  
  for (int u = 1; u <= n; ++u) 
    for (int v = u * 2; v <= n; v += u)
      cnt[u] += cnt[v];
  
  for (int c = 1; c < n; ++c) {
    if (n % (c + 1) != 0) continue;
    if (cnt[n / (c + 1)] == c + 1) cout << c << ' ';
  }
	return 0;
}


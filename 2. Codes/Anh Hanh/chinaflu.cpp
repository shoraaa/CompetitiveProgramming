#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
void file() {
	const string FILE_NAME = "chinaflu";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3e5 + 5;
ull h[N], f[N], B = 31;
int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
  cin >> n >> m;
  vector<pair<int, int>> edges;
  f[0] = 1;
  for (int i = 1; i <= n; ++i)
    f[i] = f[i-1] * B;
    
  for (int i = 0, u, v; i < m; ++i) {
    cin >> u >> v;
    if (u > v) swap(u, v);
    edges.emplace_back(u, v);
  }
  
  sort(edges.begin(), edges.end());
  edges.erase(unique(edges.begin(), edges.end()), edges.end());
  for (auto& p : edges) {
    int u = p.first, v = p.second;
    h[u] += f[v], h[v] += f[u];
  }
  
  ll res = 0;
  map<ull, int> cnt;
  for (int u = 1; u <= n; ++u) 
    res += cnt[h[u]],
    cnt[h[u]]++;
    
  for (auto& p : edges) {
    int u = p.first, v = p.second;
    if (h[u] + f[u] == h[v] + f[v]) res++;
  }
  cout << res;
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 5, S = sqrt(N) * 3;
vector<int> adj[N];
int check[N], idx[N];
bitset<N> bit[2*N / S];
int n, m, id = 0;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; 
  for (int i = 0, u, v; i < m; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
    
  vector<int> big;
  for (int u = 0; u < n; ++u) {
    if (adj[u].size() <= S) continue;
    for (int v : adj[u]) bit[id][v] = 1;
    idx[u] = id++; big.emplace_back(u);
  }
    
  ll res = 0;
  for (int u = 0; u < n; ++u) {
    for (int k : adj[u]) check[k] = 1;
    
    for (int v : adj[u]) {
      if (adj[v].size() > S) continue;
      int cur = 0;
      for (int k : adj[v]) cur += check[k];
      res += 1LL * cur * (cur - 1) / 2;
    }
    
    for (int k : adj[u]) check[k] = 0;
  }
  
  for (int u = 0; u < n; ++u) {
    if (adj[u].size() <= S) continue;
    
    for (int k : adj[u]) check[k] = 1;
    
    for (int v : adj[u]) {
      if (adj[v].size() > S) continue;
      int cur = 0;
      for (int k : adj[v]) cur += check[k];
      res += 1LL * cur * (cur - 1) / 2;
    }
    
    for (int k : adj[u]) check[k] = 0;
  }
  
  for (int i = 0; i < big.size(); ++i) for (int j = i+1; j < big.size(); ++j)
    res += (bit[idx[big[i]]] & bit[idx[big[j]]]).count();
  
  cout << res / 2;
	return 0;
}

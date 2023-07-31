#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int cmax(ll& x, ll y) {
  return x < y ? x = y, 1 : 0;
}

struct C {
  int v, w;
  C(int v, int w): v(v), w(w) {}
};
const int N = 5005, S = 10005;

int a[N]; ll dp[N][S];
vector<C> adj[N];

int s;
void dfs(int u, int p = 0, int w = 0) {
  
  for (int i = 0; i <= s; ++i)
    dp[u][i] = dp[p][i];
  
  for (auto& c : adj[u]) if (c.v != p) 
    dfs(c.v, u, c.w);

  for (int i = 0; i + w <= s; ++i)
    cmax(dp[p][i + w], dp[u][i] + a[u]);
    
}
int n;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> s;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 0, u, v, w; i < n-1; ++i)
    cin >> u >> v >> w,
    adj[u].emplace_back(v, w),
    adj[v].emplace_back(u, w);
  dfs(1);
  cout << *max_element(dp[0], dp[0] + s + 1);
	return 0;
}


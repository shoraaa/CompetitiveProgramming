#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e2 + 5, M = 1e4 + 5, MOD = 1e9 + 7;
void add(int& x, int y) {
  x += y; if (x >= MOD) x -= MOD;
}
void sub(int& x, int y) {
  x -= y; if (x < 0) x += MOD;
}
int mul(ll x, ll y) {
  return x * y % MOD;
}
int dp[N][M], sum_dp[N][M]; int lp[M];
vector<int> adj[N], fac[M], pr;
int n, m;
void dfs(int u = 0, int p = -1) {
  for (int x = 2; x <= m; ++x)
    dp[u][x] = 1;
  for (int v : adj[u]) if (v != p) {
    dfs(v, u);
    for (int x = 2; x <= m; ++x) {
      int sum = 0;
      int k = fac[x].size();
      for (int msk = 1; msk < 1 << k; ++msk) {
        int cnt = 0, val = 1, cur = 0;
        for (int i = 0; i < k; ++i) if (msk >> i & 1)
          cnt++, val *= fac[x][i];
        cur = sum_dp[v][val];
        if (cnt & 1) add(sum, cur);
        else sub(sum, cur);
      }        
      dp[u][x] = mul(dp[u][x], sum);
    }
  }
  for (int val = 2; val <= m; ++val)
    for (int y = val; y <= m; y += val)
      add(sum_dp[u][val], dp[u][y]);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	if (fopen("treegcd.inp", "r"))
  	freopen("treegcd.inp", "r", stdin),
  	freopen("treegcd.out", "w", stdout);
  cin >> n >> m;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  for (int i = 2; i <= m; ++i) {
    if (!lp[i]) lp[i] = i, pr.emplace_back(i);
    for (int p : pr) {
      if (p > lp[i] || i * p > m) break;
      lp[p * i] = p;
    }
  }
  for (int i = 2; i <= m; ++i) {
    int val = i;
    while (val > 1) {
      int x = lp[val];
      fac[i].emplace_back(x);
      while (val % x == 0) val /= x;
    }
  }
  dfs();
  int res = 0;
  for (int i = 2; i <= m; ++i)
    add(res, dp[0][i]);
  cout << res;
	return 0;
}


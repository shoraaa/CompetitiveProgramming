#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
vector<int> G[N];
int cnt[N], sum = 0;
int n, q, m = 0;
void dfs(int u, int e, int dep) {
  int cv = G[u].size() - (u != 0);
  if (dep % 2 == 0)
    cnt[abs(cv - 1)]++,
    m = max(m, abs(cv - 1));
  for (int v : G[u]) if (v != e)
    dfs(v, u, dep + 1);
}
bitset<N * 2> dp;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
    cin >> n >> q;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0, u, v; i < n-1; ++i)
      cin >> u >> v, u--, v--,
      G[u].emplace_back(v),
      G[v].emplace_back(u);
    dfs(0, -1, 0);
    for (int i = 1; i <= m; ++i) if (cnt[i] > 1) {
      if (cnt[i] & 1) cnt[i * 2] += cnt[i] / 2, cnt[i] = 1;
      else cnt[i * 2] += cnt[i] / 2 - 1, cnt[i] = 2;
      m = max(m, i * 2);
    }
    dp.reset();
    dp[n] = 1;
    for (int i = 1; i <= m; ++i)
      for (int j = 1; j <= cnt[i]; ++j) 
        dp = (dp >> i) | (dp << i);
    int ansmin = 1e9, ansmax = -1e9;
    for (int i = -n; i <= n; ++i) if (dp[i + n])
      ansmin = min(ansmin, abs(i)),
      ansmax = max(ansmax, abs(i));
    cout << (q == 1 ? ansmax : ansmin) << '\n';
    for (int u = 0; u < n; ++u) 
      G[u].clear();
  }
	return 0;
}


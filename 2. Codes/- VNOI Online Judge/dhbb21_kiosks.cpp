#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e4 + 5, M = 1e9 + 7;
void add(int& x, int y) {
	x += y; if (x >= M) x -= M;
}
int sum(int x, int y) {
	x += y; if (x >= M) x -= M; return x;
}
void sub(int& x, int y) {
	x -= y; if (x < 0) x += M;
}
int mul(ll x, ll y) {
	return x * y % M;
}
vector<int> G[N];
int dp[N][2], ans[N], c[N];
int n, k, cur_mask;
void dfs(int u = 0, int e = -1) {
	// dp[u][0] = (T dp[v][0] + 1) * !BIT(cur_msk, c[u])
	// dp[u][1] = T (dp[v][0] + dp[v][1]) - dp[u][0]
	dp[u][0] = dp[u][1] = 1;
	ans[u] = 0;
	for (int v : G[u]) if (v != e) {
		dfs(v, u);
		dp[u][0] = mul(dp[u][0], sum(dp[v][0], 1));
		dp[u][1] = mul(dp[u][1], sum(sum(dp[v][0], dp[v][1]), 1));
		add(ans[u], ans[v]);
	} 
	if (c[u] < k && cur_mask >> c[u] & 1) dp[u][0] = 0;
	sub(dp[u][1], dp[u][0]); 
	add(ans[u], dp[u][1]);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> c[i], c[i]--;
	for (int i = 0, u, v; i < n-1; ++i)
		cin >> u >> v, u--, v--,
		G[u].emplace_back(v),
		G[v].emplace_back(u);
	int res = 0;
	for (int msk = 1; msk < 1 << k; ++msk) {
		cur_mask = msk, dfs();
		if (__builtin_popcount(msk) & 1) add(res, ans[0]);
		else sub(res, ans[0]); 
	}
	cout << res << '\n';
	return 0;
}


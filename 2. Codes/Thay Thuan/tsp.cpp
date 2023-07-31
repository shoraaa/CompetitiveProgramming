#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 20;
int C[N][N];
int dp[1 << N][N];
int n, m;
int call(int msk, int u) {
	if (msk == (1 << n) - 1)
		return C[u][0] == -1 ? 1e9 : C[u][0];
	if (dp[msk][u] != -1)
		return dp[msk][u];
	int res = 1e9;
	for (int v = 0; v < n; ++v) if (!(msk >> v & 1) && C[u][v] != -1)
		res = min(res, call(msk | (1 << v), v) + C[u][v]);
	return dp[msk][u] = res;
}
void trace(int msk, int u) {
	cout << u + 1 << ' ';
	if (msk == (1 << n) - 1)
		return;
	pair<int, int> res = {1e9, -1};
	for (int v = 0; v < n; ++v) if (!(msk >> v & 1) && C[u][v] != -1)
		res = min(res, {dp[msk | (1 << v)][v] + C[u][v], v});
	if (res.second != -1)
		trace(msk | (1 << res.second), res.second);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m;
	memset(C, -1, sizeof(C));
	for (int i = 0, u, v, w; i < m; ++i)
		cin >> u >> v >> w, u--, v--,
		C[u][v] = w;
	memset(dp, -1, sizeof(dp));
	cout << call(1 << 0, 0) << '\n';
	trace(1 << 0, 0);
	return 0;
}


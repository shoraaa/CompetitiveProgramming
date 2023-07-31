#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 20;
vector<C> G[N];
int C[N][N];
int dp[1 << N][N];
int n, m;
int call(int msk, int u) {
	if (msk == (1 << n) - 1)
		return 0;
	if (dp[msk][u] != -1)
		return dp[msk][u];
	int res = 1e9;
	for (int v = 0; v < n; ++v) if (!(msk >> v & 1))
		res = min(res, call(msk | (1 << v), v));
	return dp[msk][u] = res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0, u, v, w; i < m; ++i)
		cin >> u >> v >> w, u--, v--,
		C[i][j] = w;
	memset(dp, -1, sizeof(dp));
	cout << call(0, 0);
	return 0;
}


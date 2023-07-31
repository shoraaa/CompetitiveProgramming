#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
int a[N][2];
vector<int> G[N];
ll dp[N][2];
int n;
ll call(int u, int e, int f) {
	if (dp[u][f] != -1) return dp[u][f];
	ll cur = 0;
	for (int v : G[u]) if (v != e)
		cur += call(v, u, 0);
	ll res = cur + a[u][(G[u].size() - 1 + f) & 1];
	int cnt = 0;
	for (int v : G[u]) if (v != e) {
		cur += call(v, u, 1) - call(v, u, 0); cnt++;
		res = min(res, cur + a[u][(G[u].size() - 1 + f - cnt) & 1]);
	}
	cerr << u + 1 << ' ' << f << ' ' << res << '\n';
	return dp[u][f] = res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	// tinh moi dp[v] - Z(dp[v']) 
	cin >> n;
	for (int i = 0, u, v; i < n-1; ++i)
		cin >> u >> v, u--, v--, 
		G[u].emplace_back(v),
		G[v].emplace_back(u);
	for (int i = 0; i < n; ++i)
		cin >> a[i][0];
	for (int i = 0; i < n; ++i)
		cin >> a[i][1];
	memset(dp, -1, sizeof(dp));
	cout << call(0, -1, 0);
	return 0;
}


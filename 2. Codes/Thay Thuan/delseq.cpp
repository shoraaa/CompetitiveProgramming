#include<bits/stdc++.h>
#define int ll
using namespace std;
using ll = long long;
const int N = 1024 + 5;
int a[N];
int dp[N][1 << 11];
bool vis[N][1 << 11];
int n;
int call(int pos, int msk) {
	if (pos == n) return 0;
	if (vis[pos][msk]) return dp[pos][msk];
	int res = max(0LL, a[pos] + call(pos + 1, msk));
	for (int i = 0; i <= 10; ++i) if (!(msk >> i & 1) && pos + (1 << i) <= n)
		res = max(res, call(pos + (1 << i), msk | (1 << i)));
	return vis[pos][msk] = 1, dp[pos][msk] = res;
}
signed main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i)	
		cin >> a[i];
	cout << call(0, 0);
	return 0;
}


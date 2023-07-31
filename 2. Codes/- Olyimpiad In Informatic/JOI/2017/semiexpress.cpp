#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3000 + 5;
ll a[N], dp[2][N], pos[N][N];
int cur = 1, pre = 0, cur_i;
ll res = 0;
int n, _, k;
ll A, B, C, T;
void call(int l, int r, int x, int y) {
	if (l > r) return;
	int m = (l + r) >> 1; 
	pair<ll, int> best = {-1e18, 0};
	for (int i = x; i <= min(m, y); ++i) 
		best = max(best, {dp[pre][i] + pos[cur_i-1][m-i] - a[cur_i-1] + 1, i});
	dp[cur][m] = best.first;
	res = max(res, dp[cur][m]);
	call(l, m-1, x, best.second);
	call(m+1, r, best.second, r);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	// dp[i][j] = max(dp[i-1][k] + val[j-1][j-k])
	// val[i][0] = min(a[i] + t / A, a[i+1]-1) - a[i] + 1 : t = T - (a[i] - a[0]) / B, t >= 0
	// val[i][j] = min(ans + t / A, a[i+1]-1)
	cin >> _ >> n >> k; k -= n;
	cin >> A >> B >> C;
	cin >> T;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n-1; ++i) {
		ll original_t = T - (a[i] - a[0]) * B;
		if (original_t < 0) break;
		pos[i][0] = min(a[i] + original_t / A, a[i+1]-1);
		for (int j = 1; j <= k; ++j) {
			pos[i][j] = pos[i][j-1];
			ll t = original_t - (pos[i][j-1] + 1 - a[i]) * C;
			if (t < 0) break;
			pos[i][j] = min(pos[i][j-1] + 1 + t / A, a[i+1]-1);
		}
	}
	for (int i = 1; i < n; ++i) {
		cur_i = i;
		call(0, k, 0, k);
		swap(cur, pre);
	}
	res += ((a[n-1] - a[0]) * B <= T) - 1;
	cout << res;
	return 0;
}


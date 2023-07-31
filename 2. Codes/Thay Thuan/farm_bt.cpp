#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e4 + 5;
int a[N];
ll dp[11][N];
int n, k, q, p;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> k >> q >> p;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	deque<int> dq;
	for (int i = 0; i < n; ++i) {
		int cur = i % (k + 1), pre = (i - 1) % (k + 1), pre_k = (i - k) % (k + 1);
		if (pre < 0) pre += k + 1;
		if (pre_k < 0) pre_k += k + 1;
		for (int j = 0; j <= q; ++j) {
			dp[cur][j] = dp[pre][j];
			for (int l = 1; l <= p && l <= j; ++l)
				dp[cur][j] = max(dp[cur][j], dp[pre_k][j-l] + ll(a[i]) * l);
		}
	}
	cout << dp[(n - 1) % (k + 1)][q];
	return 0;
}


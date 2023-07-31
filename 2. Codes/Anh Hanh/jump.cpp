#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "jump";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2000 + 5;
ll a[N][4], dp[2][1 << 4][N], max_dp[2][1 << 4][N];
int n, m, K;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n >> m >> K;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> a[i][j];
	// dp[2][mask][k] 
	// xet den hang i, chon may thang trong mask, lay k thang
	// max_dp[2][mask][k]
	// xet den hang i, nhung o trong mask co the duoc chon hoac ko, lay k thang
	vector<int> cor;
	for (int mask = 0; mask < 1 << m; ++mask) {
		int f = 0;
		for (int i = 1; i < m; ++i) if ((mask >> i & 1) && (mask >> (i - 1) & 1)) {f = 1; break;} 
		if (f) continue;
		cor.emplace_back(mask);
	}
//	int filter = (1 << m) - 1;
//	memset(max_dp[1], -0x3f, sizeof(max_dp[1])); 
//	for (int mask = 0; mask < 1 << m; ++mask)
//		max_dp[1][mask][0] = 0;
	memset(dp, -0x3f, sizeof(dp));
	ll res = dp[0][0][0];
	for (int mask : cor) {
		int sum = 0;
		for (int j = 0; j < m; ++j) if (mask >> j & 1) sum += a[0][j];
		dp[0][mask][__builtin_popcount(mask)] = sum;	
	}
	int filter = (1 << m) - 1;
	for (int i = 1; i < n; ++i) {
		int cur = i & 1, pre = cur ^ 1;
		//memset(max_dp[cur], -0x3f, sizeof(max_dp[cur]));
		memset(dp[cur], -0x3f, sizeof(dp[cur]));
		for (int k = 0; k <= K; ++k) {
			for (int mask : cor) if (__builtin_popcount(mask) <= k) {
				int sum = 0, pre_k = k - __builtin_popcount(mask);
				for (int j = 0; j < m; ++j) if (mask >> j & 1) sum += a[i][j];
				dp[cur][mask][k] = dp[pre][0][pre_k] + sum;
				int can_mask = ~mask & filter;
				for (int pre_mask = can_mask; pre_mask; pre_mask = (pre_mask - 1) & can_mask)
					dp[cur][mask][k] = max(dp[cur][mask][k], dp[pre][pre_mask][pre_k] + sum);
				//dp[cur][mask][k] = max_dp[pre][~mask & filter][k - __builtin_popcount(mask)] + sum;
			}
//			for (int mask = 0; mask < 1 << m; ++mask) {
//				max_dp[cur][mask][k] = dp[cur][mask][k];
//				for (int j = 0; j < m; ++j) if (mask >> j & 1)
//					max_dp[cur][mask][k] = max(max_dp[cur][mask][k], max_dp[cur][mask ^ (1 << j)][k]);
//			}
		}
	}
	for (int mask : cor) 
		res = max(res, dp[(n - 1) & 1][mask][K]);
	cout << res;
	//cout << max_dp[(n - 1) & 1][(1 << m) - 1][K];
	
	return 0;
}


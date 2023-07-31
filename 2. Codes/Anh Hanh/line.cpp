#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "line";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2e5 + 5, K = 300 + 5, M = 998244353;
inline void add(int& x, int y) {
	x += y; if (x >= M) x -= M;
}
inline int mul(ll x, ll y) {
	return x * y % M;
}
int pw(ll x, ll k) {
	ll res = 1;
	for (; k; k >>= 1, x = x * x % M) 
		if (k & 1) res = res * x % M;
	return res;
}
int fac[N + K], inv[N + K], a[N], dp[2][K];
inline int C(int n, int k) {
	if (n < k) return 0;
	return ll(fac[n]) * inv[k] % M * inv[n-k] % M;
}
int n, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
	cin >> n >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	sort(a, a + n, greater<int>());
	vector<int> c; c.reserve(n);
	for (int i = 0; i < n;) {
		int j = i;
		while (j < n && a[j] == a[i]) j++;
		c.emplace_back(j - i), i = j;
	}
	
	fac[0] = inv[0] = 1;
	for (int i = 1; i <= n + k; ++i)
		fac[i] = mul(fac[i-1], i), inv[i] = pw(fac[i], M-2);
	
	dp[0][0] = fac[c[0]];
	int placed = c[0];
	n = c.size();
	for (int i = 1; i < n; ++i) {
		int cur = i & 1, pre = cur ^ 1, cnt = c[i];
		memset(dp[cur], 0, sizeof(dp[cur]));
		for (int j = 0; j <= k; ++j) for (int t = 0; t <= cnt && t <= j; ++t) {
			int ans = mul(dp[pre][j-t], C(placed+t-1, t));
			add(dp[cur][j], mul(ans, fac[cnt]));
		}
		placed += cnt;
	}	
	int res = 0;
	for (int i = 0; i <= k; ++i)
		add(res, dp[(n-1)&1][i]);
	cout << res;
	return 0;
}


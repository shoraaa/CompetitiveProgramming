#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2000 + 5, M = 1e9 + 7;
void add(int& x, int y) {
	x += y; if (x >= M) x -= M;
}
int sum(int x, int y) {
	add(x, y); return x;
}
int mul(ll x, ll y) {
	return x * y % M;
}
int pw(ll x, ll k) {
	ll res = 1;
	for (; k; k >>= 1, x = x * x % M)
		if (k & 1) res = res * x % M;
	return res;
}
int n, k;
int dp[N][N];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> k;
	// dp[i][j] la so phuong an cho i xe phan phoi den j khach
	// dp[i][j] = Z dp[i-1][j-k] * A[k][j]
	// dp[i][j] = dp[i][j-1] * (i + j - 1)
	dp[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		dp[i][0] = 1;
		for (int j = 1; j <= k; ++j)
			dp[i][j] = mul(dp[i][j-1], i + j - 1);
	}
	cout << dp[n][k];
	return 0;
}


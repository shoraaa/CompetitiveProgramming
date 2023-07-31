#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int M = 1e9 + 7;
void add(int& x, int y) {
	x += y; if (x >= M) x -= M;
}
int sum(int x, int y) {
	add(x, y); return x;
}
int dif(int x, int y) {
	x -= y; if (x < 0) x += M; return x;
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
int C(ll n, int k) {
	if (n < k) return 0;
	int tu = 1, mau = 1;
	n %= M;
	for (int i = 1; i <= k; ++i)
		tu = mul(tu, n-i+1),
		mau = mul(mau, i);
	// cerr << n << ' ' << k << ' ' << tu/mau << '\n';
	return mul(tu, pw(mau, M - 2));
}
const int N = 1e6 + 5;
int dp[1000 + 5][5000 + 5];
unordered_map<int, int> sum_dp[1000 + 5];
int n;
ll k;
int a[N];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	if (n == 1) 
		return cout << (k == a[1]), 0;
	if (n > 1000) 
		return cout << C(k-1, n-1), 0;
	// dp[i][j] la so cach phan j diem ban le vao i chi nhanh
	// dp[i][j] = Z dp[i-1][j - a[i] * b] : b > 0
	// dp[i][j] = sum_dp[i-1][j]
	dp[0][0] = sum_dp[0][0] = 1;
	for (int j = 1; j <= k; ++j) {
		for (int i = 1; i <= n; ++i) {
			dp[i][j] = dif(sum_dp[i-1][j % a[i]], dp[i-1][j]);
			// printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
			// update
			if (i < n)
				add(sum_dp[i][j % a[i + 1]], dp[i][j]);  
		}
	}
	cout << dp[n][k];
	return 0;
}


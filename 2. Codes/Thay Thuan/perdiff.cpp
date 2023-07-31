#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 5, M = 1e9 + 7;
int dp[N][N][2];
void add(int& x, int y) {
	x += y; if (x >= M) x -= M;
}
int mul(ll x, ll y) {
	return x * y % M;
}
int f(int n, int k, int b) {
	if (n < 0 || k < 0) return 0;
	if (n == 1) return k == 0 && b == 0;
	if (dp[n][k][b] != -1)
		return dp[n][k][b];
	int res = 0;
	if (b == 0) {
		add(res, mul(f(n-1, k, 0), max(0, n - k - 2)));
		add(res, mul(f(n-1, k, 1), max(0, n - k - 1)));
		add(res, mul(f(n-1, k+1, 0), (k + 1)));
		add(res, mul(f(n-1, k+1, 1), k));
	} else {
		add(res, mul(f(n-1, k-1, 0), 2));
		add(res, f(n-1, k, 1));
		add(res, f(n-1, k-1, 1));
	}
	return dp[n][k][b] = res;
}
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	memset(dp, -1, sizeof(dp));
	cout << f(n, 0, 0);
	return 0;
}


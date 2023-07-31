#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "pushingrocks";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2000 + 5, M = 998244353;
void add(int& x, int y) {
	x += y; if (x >= M) x -= M; 
}
int a[N][N], f[N][N], dp[N][N][2];
int n, m;
int sum(int x0, int y0, int x1, int y1) {
	return f[x1][y1] - f[x0-1][y1] - f[x1][y0-1] + f[x0-1][y0-1];
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
	cin >> n >> m;
	char c;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> c,
			a[i][j] = c == 'R',
			f[i][j] = f[i-1][j] + f[i][j-1] - f[i-1][j-1] + a[i][j];
	if (n == 1 && m == 1) 
		return cout << (a[1][1] == 0), 0;
	// dp[i][j][0] = Z dp[i][k][1] : k < j, (m-k) >= sum(k + 1, m)
	dp[1][1][0] = dp[1][1][1] = a[1][1] == 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			for (int k = j-1; ~k; --k) if (m - j >= sum(i, k+1, i, m))
				add(dp[i][j][0], dp[i][k][1]);
			for (int k = i-1; ~k; --k) if (n - i >= sum(k+1, j, n, j))
				add(dp[i][j][1], dp[k][j][0]);
			cerr << dp[i][j][0] << ',' << dp[i][j][1] << " \n"[j==m];
		}
	cout << (dp[n][m][0] + dp[n][m][1]) % M;
	return 0;
}

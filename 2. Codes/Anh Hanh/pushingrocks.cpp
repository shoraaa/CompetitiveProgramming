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
int diff(int x, int y) {
	x -= y; if (x < 0) x += M; return x;
}
struct bit_prefix {
	vector<int> bit;
	int n;
	bit_prefix(int n): n(n), bit(n + 5) {}
	int get(int i) {
		int res = 0;
		for (; i; i -= i & -i)
			add(res, bit[i]);
		return res;
	}
	void update(int i, int v) {
		for (; i <= n; i += i & -i)
			add(bit[i], v);
	}
	void clear() {
		vector<int>(n + 5).swap(bit);
	}
};
int a[N][N], f[N][N], dp[N][N][2];
int n, m;
int sum(int x0, int y0, int x1, int y1) {
	return f[x1][y1] - f[x0-1][y1] - f[x1][y0-1] + f[x0-1][y0-1];
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
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
	
	bit_prefix row(m);
	vector<bit_prefix> col(m + 1, bit_prefix(n));
	for (int i = 1; i <= n; ++i) {
		row.clear();
		for (int j = 1; j <= m; ++j) {
			int lo = 1, hi = j-1, mid, ans = -1;
			while (lo <= hi) {
				mid = (lo + hi) >> 1;
				if (m - j >= sum(i, mid+1, i, m))
					ans = mid,
					hi = mid - 1;
				else lo = mid + 1;
			}
			if (ans != -1) dp[i][j][0] = diff(row.get(j - 1), row.get(ans - 1));
			
			lo = 1, hi = i-1, mid, ans = -1;
			while (lo <= hi) {
				mid = (lo + hi) >> 1;
				if (n - i >= sum(mid+1, j, n, j))
					ans = mid,
					hi = mid - 1;
				else lo = mid + 1;
			}
			if (ans != -1) dp[i][j][1] = diff(col[j].get(i - 1), col[j].get(ans - 1));
			
			row.update(j, dp[i][j][1]);
			col[j].update(i, dp[i][j][0]);
		}
	}
	cout << (dp[n][m][0] + dp[n][m][1]) % M;
	return 0;
}


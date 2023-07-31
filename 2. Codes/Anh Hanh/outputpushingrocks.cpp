#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2000 + 5, M = 998244353;
int a[N][N], f[N][N];
int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m;
	char c;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			cin >> c;
			a[i][j] = c == 'R';
			f[i][j] = f[i-1][j] + f[i][j-1] - f[i-1][j-1] + a[i][j];
		}
	// dp[i][j][0/1/2] la dang ko day vien nao/ day sang phai/ day sang trai
	queue<S> q;
	q.emplace(i, j, 0, 1);
	while (!q.empty()) {
		S s = q.front(); q.pop();
		if (j < m) {
			int rock = a[i][j+1];
			if (
		}
	}
	return 0;
}


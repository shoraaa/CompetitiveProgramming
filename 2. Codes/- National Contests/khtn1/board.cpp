#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int MOD = 998244353;
int n, m, k;
namespace task_1 {
	const int N = 10, M = 100;
	int a[N][M], tmp[2][N], dp[M][1 << N];
	vector<int> cor[1 << N];
	int call(int col, int msk) {
		if (col == m) return 1;
		if (dp[col][msk] != -1) 
			return dp[col][msk];
		int res = 0;
		for (int nxt : cor[msk]) {
			bool f = 0;
			for (int i = 0; i < n; ++i) {
				f |= (a[i][col] != (nxt >> i & 1)) && (a[i][col] != 2);
				if (f) break;
			}
			if (f) continue;
			res = (res + call(col + 1, nxt)) % MOD;
		}
		return dp[col][msk] = res;
	}
	void solve() {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) a[i][j] = 2;
		for (int x, y, v; k--;) {
			cin >> x >> y >> v; x--, y--;
			if (v == 0) v = 1;
			else if (v == 1) v = 0;
			a[x][y] = v; 
		}
		for (int msk1 = 0; msk1 < 1 << n; ++msk1) for (int msk2 = 0; msk2 < 1 << n; ++msk2) {
			for (int i = 0; i < n; ++i) tmp[0][i] = msk1 >> i & 1, tmp[1][i] = msk2 >> i & 1;
			bool f = 0;
			for (int i = 0; i < n-1; ++i) if ((tmp[0][i] + tmp[0][i+1] + tmp[1][i] + tmp[1][i+1]) & 1)  {f = 1; break;}			
			if (f) continue;
			cor[msk1].emplace_back(msk2);
		}
		memset(dp, -1, sizeof(dp));
		int res = 0;
		for (int beg = 0; beg < 1 << n; ++beg) {
			bool f = 0;
			for (int i = 0; i < n; ++i) f |= (a[i][0] != (beg >> i & 1)) && (a[i][0] != 2);
			if (f) continue;
			res = (res + call(1, beg)) % MOD;
		}
		cout << res;
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m >> k;
	if (n <= 10 && m <= 100) task_1::solve();
	else assert(0);
	return 0;
}


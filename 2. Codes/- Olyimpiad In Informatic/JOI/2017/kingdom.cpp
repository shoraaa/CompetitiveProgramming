#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2000 + 5;
int a[N][N];
int n, m, ma, mi;
int top_left(int x) {
	for (int i = 1, cur_r = m; i <= n; ++i) {
		for (int j = cur_r; j; --j) 
			if (ma - a[i][j] > x) cur_r = j - 1;
		for (int j = cur_r + 1; j <= m; ++j)
			if (a[i][j] - mi > x) return 0;
	}
	return 1;
}
int bot_left(int x) {
	for (int i = n, cur_r = m; i; --i) {
		for (int j = cur_r; j; --j) 
			if (ma - a[i][j] > x) cur_r = j - 1;
		for (int j = cur_r + 1; j <= m; ++j)
			if (a[i][j] - mi > x) return 0;
	}
	return 1;
}
int top_right(int x) {
	for (int i = 1, cur_r = m; i <= n; ++i) {
		for (int j = cur_r; j; --j) 
			if (a[i][j] - mi > x) cur_r = j - 1;
		for (int j = cur_r + 1; j <= m; ++j)
			if (ma - a[i][j] > x) return 0;
	}
	return 1;
}
int bot_right(int x) {
	for (int i = n, cur_r = m; i; --i) {
		for (int j = cur_r; j; --j) 
			if (a[i][j] - mi > x) cur_r = j - 1;
		for (int j = cur_r + 1; j <= m; ++j)
			if (ma - a[i][j] > x) return 0;
	}
	return 1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	// partition to 2 groups, each have its it_max - it_min <= x 
	// <=> partition to 2 groups, one have all_max - it_min <= x, one have it_max - all_min <= x
	// because it_max <= all_max, it_min >= all_min
	cin >> n >> m;
	ma = 0, mi = 1e9;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> a[i][j], ma = max(ma, a[i][j]), mi = min(mi, a[i][j]);
	int lo = 0, hi = ma - mi, mid, ans = 0;
	while (lo <= hi) {
		mid = (lo + hi) >> 1;
		if (top_right(mid) || top_left(mid) || bot_right(mid) || bot_left(mid))
			ans = mid,
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	cout << ans;
	return 0;
}


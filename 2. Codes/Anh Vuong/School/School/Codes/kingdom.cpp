#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int a[N][N], n, m, mx, mn;
int b[N][N], c[N][N];

void input() {
	mx = INT_MIN; mn = INT_MAX;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
			mx = max(mx, a[i][j]);
			mn = min(mn, a[i][j]);
		}
}

bool check(int x) {
	int l = 0; bool ok = 1;
	for (int i = 1; i <= n; i++) {
		int k = -1, cur = INT_MIN;
		for (int j = 1; j < l; j++)
			cur = max(cur, a[i][j]);
		for (int j = l; j <= m; j++) {
			if (j > 0)
				cur = max(cur, a[i][j]);
			if (cur <= x + mn &&
			b[i][j + 1] >= mx - x) {
				k = j; break;
			}
		}
		if (k < 0) {
			ok = 0; break;
		}
		l = k;
	}
	if (ok) return 1;
	l = 0; ok = 1;
	for (int i = 1; i <= n; i++) {
		int k = -1, cur = INT_MAX;
		for (int j = 1; j < l; j++)
			cur = min(cur, a[i][j]);
		for (int j = l; j <= m; j++) {
			if (j > 0)
				cur = min(cur, a[i][j]);
			if (cur >= mx - x &&
			c[i][j + 1] <= x + mn) {
				k = j; break;
			}
		}
		if (k < 0) {
			ok = 0; break;
		}
		l = k;
	}
	return ok;
}

int process() {
	for (int i = 1; i <= n; i++) {
		b[i][m + 1] = INT_MAX;
		c[i][m + 1] = INT_MIN;
		for (int j = m; j > 0; j--) {
			b[i][j] = min(a[i][j], b[i][j + 1]);
			c[i][j] = max(a[i][j], c[i][j + 1]);
		}
	}
	int lo = 0, hi = 1e9;
	while (lo < hi) {
		int mi = (lo + hi) / 2;
		if (check(mi)) hi = mi;
		else lo = mi + 1;
	}
	return hi;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	input(); int res = process();
	reverse(a + 1, a + n + 1);
	res = min(res, process());
	cout << res << '\n';
}


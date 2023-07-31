#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 200 + 5, M = 4e4 + 5, oo = 1e9;
int a[N], b[N], dmin[N][M], dmax[N][M];
int n, m = 0;
vector<int> trace_min(int x) {
	// tong a = x, tong b nho nhat
	vector<int> res(n + 1);
	for (int i = n; i; --i) {
		if (x >= a[i] && dmin[i][x] == dmin[i-1][x - a[i]] + b[i]) 
			x -= a[i], res[i] = 1;
	}
	return res;
}
vector<int> trace_max(int x) {
	// tong a = x, tong b lon nhat
	vector<int> res(n + 1);
	for (int i = n; i; --i) {
		if (x >= a[i] && dmax[i][x] == dmax[i-1][x - a[i]] + b[i]) 
			x -= a[i], res[i] = 1;
	}
	return res;
}
void trace(int x, int y) {
	vector<int> tx = trace_min(x),
							ty = trace_max(y);
	vector<int> rx, ry;
	for (int i = 1; i <= n; ++i) {
		if (tx[i] && ty[i]) continue;
		if (tx[i]) rx.emplace_back(i);
		if (ty[i]) ry.emplace_back(i);	
	}
	cout << "YES\n";
	cout << rx.size() << ' '; 
	for (int v : rx) cout << v << ' ';
	cout << '\n';
	cout << ry.size() << ' '; 
	for (int v : ry) cout << v << ' ';
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i], m += a[i];
	for (int i = 1; i <= n; ++i)
		cin >> b[i];
	for (int i = 1; i <= m; ++i)
		dmin[0][i] = oo, dmax[0][i] = -oo;
	for (int i = 1; i <= n; ++i)
		for (int j = m; j; --j)
			dmin[i][j] = min(dmin[i-1][j], j >= a[i] ? dmin[i-1][j-a[i]] + b[i] : oo),
			dmax[i][j] = max(dmax[i-1][j], j >= a[i] ? dmax[i-1][j-a[i]] + b[i] : -oo);
	pair<int, int> mx = {0, 0};
	for (int i = 1; i <= m; ++i) {
		if (mx.first > dmin[n][i])
			return trace(i, mx.second), 0;
		mx = max(mx, {dmax[n][i], i}); 
	}
	cout << "NO";
	return 0;
}


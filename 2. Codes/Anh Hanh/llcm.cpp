#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "llcm";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e6 + 5, M = 1e7 + 5;
int a[N];
int b[M][2];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	pair<ll, pair<int, int>> res = {1e18, {-1, -1}};
	int mn = a[1], mx = a[1];
	for (int i = 1; i <= n; ++i) {
		mx = max(mx, a[i]), mn = min(mn, a[i]);
		if (!b[a[i]][0]) b[a[i]][0] = i;
		else b[a[i]][1] = i;
	}
	for (int g = 1; g <= mx; ++g) {
		vector<int> v;
		for (int h = g; h <= mx; h += g) {
			if (b[h][0]) v.emplace_back(b[h][0]);
			if (b[h][1]) v.emplace_back(b[h][1]);
			if (v.size() >= 2) break;
		}
		if (v.size() >= 2) res = min(res, {ll(a[v[0]]) * a[v[1]] / g, {v[0], v[1]}});
	}
	if (res.second.first > res.second.second) swap(res.second.second, res.second.first);
	cout << res.second.first << ' ' << res.second.second << '\n';
	return 0;
}

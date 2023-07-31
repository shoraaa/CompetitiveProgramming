#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
pair<int, int> a[N];
int b[N];
int n, m;
int check(int k) {
	for (int i = m-k, j = 0; i < m; ++i, ++j) {
		while (j < n && a[j].second > b[i]) j++;
		if (j == n) return 0;
	}
	return 1;
		
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> a[i].second >> a[i].first;
	for (int i = 0; i < m; ++i)
		cin >> b[i];
	sort(a, a + n);
	sort(b, b + m);
	int lo = 0, hi = min(n, m), mid, ans = 0;
	while (lo <= hi) {
		mid = (lo + hi) >> 1;
		if (check(mid))
			ans = mid,
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	cout << ans;
	return 0;
}


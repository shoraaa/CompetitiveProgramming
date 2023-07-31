#include <bits/stdc++.h>
using namespace std;
const int N = 55, oo = 1e9 + 123;
int n, m, a[N];
int dp[N][N];
int calc(int l, int r) {
	if (l == r) return 1;
	int ans = oo, tmp = 0;
	for (int i = l, j; i <= r; ++i)
		if (a[i] != a[l]) {
			j = i;
			while (j <= r && a[j] != a[l]) j++;
			tmp += calc(i, j-1);
			i = j-1;
		} 
	ans = min(ans, tmp+1);
	for (int i = l; i < r; ++i)
		ans = min(ans, calc(l, i) + calc(i+1, r));
	return dp[l][r] = ans;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	if (fopen("EMAIL.inp", "r"))
		freopen("EMAIL.inp", "r", stdin),
		freopen("EMAIL.out", "w", stdout);
	cin >> n;
	vector<int> comp;
	for (int i = 0; i < n; ++i) 
		cin >> a[i], comp.emplace_back(a[i]);
	memset(dp, -1, sizeof(dp));
	cout << calc(0, n-1);
	return 0;
}

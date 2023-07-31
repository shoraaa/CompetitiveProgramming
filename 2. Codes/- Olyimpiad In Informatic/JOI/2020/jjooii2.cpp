#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2e5 + 5;
int a[N], J[N], O[N], I[N];
int n, K;
int check(int l, int r) {
	/* 
	doan (l, r] thoa man <=> ton tai i, j, k thoa man
	l < i < j < r
	J[i] >= K + J[l]
	O[j] >= K + O[i]
	I[r] >= K + I[j]
	*/
	if (r - l < K * 3) return 0;
	int i = lower_bound(J + l + 1, J + n, K + J[l]) - J;
	if (i >= r) return 0;
	int j = lower_bound(O + i + 1, O + n, K + O[i]) - O;
	if (j >= r) return 0;
	return I[r] >= K + I[j];
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> K;
	char c;
	for (int i = 1; i <= n; ++i) 
		cin >> c,
		J[i] = J[i-1] + (c == 'J'),
		O[i] = O[i-1] + (c == 'O'),
		I[i] = I[i-1] + (c == 'I');
	
	int res = -1;
	for (int l = 0, r = 1; l < n; ++l) {
		// (l, r]
		while (r <= n && !check(l, r)) r++;
		if (r == n + 1) break;
		res = res == -1 ? r - l - K * 3 : min(res, r - l - K * 3);
	}
	cout << res;
	return 0;
}


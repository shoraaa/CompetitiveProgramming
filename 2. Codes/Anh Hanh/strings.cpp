#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "strings";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int M = 1e9 + 19972207, N = 1e6 + 5;
int l;
string a, b;
int dp[N][2][2];
ll call(int pos, int bigger, int smaller) {
	if (pos == l) return bigger && (smaller | pos < b.size());
	if (pos >= a.size()) bigger = 1;
	if (pos >= b.size() && !smaller) return 0;
	if (dp[pos][bigger][smaller] != -1) 
		return dp[pos][bigger][smaller];
	ll res = 0;
	char lw = bigger ? 'a' : a[pos], up = smaller ? 'z' : b[pos];
	for (char c = lw; c <= up; ++c) {
	 int n_bigger = bigger; if (!bigger) n_bigger |= c > a[pos];
		int n_smaller = smaller; if (!smaller) n_smaller |= c < b[pos];
		res = (res + call(pos + 1, n_bigger, n_smaller)) % M;
	}
	return dp[pos][bigger][smaller] = res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> l >> a >> b;
//	memset(dp, -1, sizeof(dp));
//	cout << call(0, 0, 0);
//	
	for (int bigger = 0; bigger <= 1; ++bigger) for (int smaller = 0; smaller <= 1; ++smaller)
		dp[l][bigger][smaller] = bigger && (smaller | l < b.size());
	for (int pos = l-1; ~pos; --pos) for (int bigger = 1; bigger >= 0; --bigger) for (int smaller = 0; smaller <= 1; ++smaller) {
		if (!bigger && pos >= a.size()) {dp[pos][bigger][smaller] = dp[pos][1][smaller]; continue;};
		if (!smaller && pos >= b.size()) continue;
		int res = 0;
		char lw = bigger ? 'a' : a[pos], up = smaller ? 'z' : b[pos];
		for (char c = lw; c <= up; ++c) {
			int n_bigger = bigger; if (!bigger) n_bigger |= c > a[pos];
			int n_smaller = smaller; if (!smaller) n_smaller |= c < b[pos];
			res += dp[pos + 1][n_bigger][n_smaller];
			if (res >= M) res -= M;
		}
		dp[pos][bigger][smaller] = res;
	}
	cout << dp[0][0][0];
	return 0;
}


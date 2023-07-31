#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "removepalin";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
string s;
const int N = 1e6 + 5;
int dp[N][5][5];
int n;
char shift(char c, int x) {
	c += x; 
	if (c >= 'z') c -= 26;
	if (c <= 'a') c += 26;
	return c;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> s; n = s.size();
	if (n == 1) return cout << 0, 0;
	// bien doi sao cho voi moi i thi s[i] != s[i-1] va s[i] != s[i-2]
	// dp[i][c1][c2] la chi phi nho nhat bien doi i ki tu dau sao cho s[i] != c1 va s[i] != c2
	int res = 1e9;
	memset(dp, 0x3f, sizeof(dp));
	for (int c = -2; c <= 2; ++c) for (int c1 = -2; c1 <= 2; ++c1) 
		if (shift(s[1], c) != shift(s[0], c1)) dp[1][c+2][c1+2] = abs(c) + abs(c1);
	for (int i = 2; i < n; ++i) for (int c1 = -2; c1 <= 2; ++c1) for (int c2 = -2; c2 <= 2; ++c2) {
		char ch1 = shift(s[i-1], c1), ch2 = shift(s[i-2], c2);
		for (int c = -2; c <= 2; ++c) {
			char ch = shift(s[i], c);
			if (ch == ch1 || ch == ch2) continue;
			dp[i][c+2][c1+2] = min(dp[i][c+2][c1+2], dp[i-1][c1+2][c2+2] + abs(c));
		}
	}
	for (int c = -2; c <= 2; ++c) for (int c1 = -2; c1 <= 2; ++c1) 
		res = min(res, dp[n-1][c+2][c1+2]);
	cout << res;
	return 0;
}


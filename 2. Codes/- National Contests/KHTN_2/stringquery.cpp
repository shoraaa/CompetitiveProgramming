#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2000 + 5;
int a[N];
int cost[3][3][3], f[3], dp[N][3];
int n, q;
struct Q {
	int l, i;
	Q(int l, int i): l(l), i(i) {}
};
vector<Q> qrs[N];
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	string s;
	cin >> n >> q >> s;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '?') a[i] = -1;
		else a[i] = s[i] - '0';
	}
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			for (int k = 0; k < 3; ++k)
				cin >> cost[i][j][k];
	for (int i = 0; i < 3; ++i)
		cin >> f[i];
	for (int i = 0, l, r; i < q; ++i) 
		cin >> l >> r, l--, r--, cerr << l << ' ' << r << '\n',
		qrs[r].emplace_back(l, i);
	vector<int> res(q);
	return 0;
	for (int i = 0; i < n; ++i) {
		// dp[i][c] = min(dp[i+1][c'] + a[c][s[i]][c'])
		memset(dp, 0x3f, sizeof(dp));
		dp[i + 1][0] = dp[i + 1][1] = dp[i + 1][2] = 0;
		for (int j = i; ~j; --j) {
			if (a[j] == -1) {
				for (int naj = 0; naj < 3; ++naj) {
					dp[j][0] = min(dp[j][0], f[naj] + min({dp[j+1][0] + cost[0][naj][0], dp[j+1][1] + cost[0][naj][1], dp[j+1][2] + cost[0][naj][2]}));
					dp[j][1] = min(dp[j][1], f[naj] + min({dp[j+1][0] + cost[1][naj][0], dp[j+1][1] + cost[1][naj][1], dp[j+1][2] + cost[1][naj][2]}));
					dp[j][2] = min(dp[j][2], f[naj] + min({dp[j+1][0] + cost[2][naj][0], dp[j+1][1] + cost[2][naj][1], dp[j+1][2] + cost[2][naj][2]}));
				}
			} else {
				dp[j][0] = min({dp[j+1][0] + cost[0][a[j]][0], dp[j+1][1] + cost[0][a[j]][1], dp[j+1][2] + cost[0][a[j]][2]});
				dp[j][1] = min({dp[j+1][0] + cost[1][a[j]][0], dp[j+1][1] + cost[1][a[j]][1], dp[j+1][2] + cost[1][a[j]][2]});
				dp[j][2] = min({dp[j+1][0] + cost[2][a[j]][0], dp[j+1][1] + cost[2][a[j]][1], dp[j+1][2] + cost[2][a[j]][2]});
			}
		}
		for (auto& qr : qrs[i]) {
			if (a[qr.l] == -1) {
				res[qr.i] = min({dp[qr.l + 1][0] + f[0], dp[qr.l + 1][1] + f[1], dp[qr.l + 1][2] + f[2]});
			} else {
				res[qr.i] = dp[qr.l + 1][a[qr.l]];
			}
		}
	}
	for (int i = 0; i < q; ++i)
		cout << res[i] << '\n';
	
	return 0;
}


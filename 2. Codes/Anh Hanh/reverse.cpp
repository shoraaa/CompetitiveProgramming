#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "reverse";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
string s[N];
ll a[N], dp[N][2];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
		cin >> s[i];
	memset(dp, 0x3f, sizeof(dp));
	ll oo = dp[0][0];
	dp[0][0] = 0;
	dp[0][1] = a[0];
	for (int i = 1; i < n; ++i) {
		string s_i = s[i], s_ri = s_i;
		reverse(s_ri.begin(), s_ri.end()); 
		string t_i = s[i - 1], t_ri = t_i;
		reverse(t_ri.begin(), t_ri.end());
		if (s_i >= t_i) dp[i][0] = min(dp[i][0], dp[i-1][0]); 
		if (s_i >= t_ri) dp[i][0] = min(dp[i][0], dp[i-1][1]); 
		if (s_ri >= t_i) dp[i][1] = min(dp[i][1], dp[i-1][0] + a[i]); 
		if (s_ri >= t_ri) dp[i][1] = min(dp[i][1], dp[i-1][1] + a[i]); 
	}
	ll res = min(dp[n-1][0], dp[n-1][1]);
	if (res == oo) cout << -1;
	else cout << res;
	return 0;
}


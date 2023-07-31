#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1000 + 5;
int a[N], b[N];
int dp[N][N];
int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	cin >> m;
	for (int i = 1; i <= m; ++i)
		cin >> b[i];
	pair<int, pair<int, int>> res;
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
		dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		if (a[i] == b[j]) dp[i][j] = dp[i-1][j-1] + 1;
		res = max(res, {dp[i][j], {i, j}});
	}
	cout << res.first;
//	stack<int> st;
//	for (int i = res.second.first, j = res.second.second; i > 0 && j > 0;) {
//		if (a[i] == b[j]) st.emplace(a[i]), i--, j--;
//		else if (dp[i-1][j] > dp[i][j-1]) i--;
//		else j--;
//	}
//	while (!st.empty()) 
//		cout << st.top() << ' ', st.pop();
	return 0;
}


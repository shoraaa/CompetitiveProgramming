#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
int n;
int a[N], b[N], tmin[N], tmax[N], res[N];
pair<int, int> dp[N][2];
int trace_min() {
	for (int i = 1; i <= n*2; ++i) {
		dp[i][0].first = 1e9;
		if (b[i] >= a[i-1]) dp[i][0] = min(dp[i][0], {dp[i-1][1].first, 1});
		if (b[i] >= b[i-1]) dp[i][0] = min(dp[i][0], {dp[i-1][0].first, 0});
		
		dp[i][1].first = 1e9;
		if (a[i] >= a[i-1]) dp[i][1] = min(dp[i][1], {dp[i-1][1].first + 1, 1});
		if (a[i] >= b[i-1]) dp[i][1] = min(dp[i][1], {dp[i-1][0].first + 1, 0});
	}
	if (dp[n * 2][0].first > n && dp[n * 2][1].first > n) 
		return 0;
	pair<int, int> cur; cur.first = n * 2;
	cur.second = dp[n * 2][0].first < dp[n * 2][1].first ? 0 : 1;
	while (cur.first > 0) {
		tmin[cur.first] = cur.second;
		cur.second = dp[cur.first][cur.second].second;
		cur.first--;		
	}
	return 1;
}
int trace_max() {
	for (int i = 1, t; i <= n*2; ++i) {
		dp[i][0].first = -1e9;
		if (!tmin[i] && b[i] >= a[i-1]) dp[i][0] = max(dp[i][0], {dp[i-1][1].first, 1});
		if (!tmin[i] && b[i] >= b[i-1]) dp[i][0] = max(dp[i][0], {dp[i-1][0].first, 0});
		
		dp[i][1].first = -1e9;
		if (a[i] >= a[i-1]) dp[i][1] = max(dp[i][1], {dp[i-1][1].first + 1, 1});
		if (a[i] >= b[i-1]) dp[i][1] = max(dp[i][1], {dp[i-1][0].first + 1, 0});
	}
	if (dp[n * 2][0].first < n && dp[n * 2][1].first < n) 
		return 0;
	pair<int, int> cur; cur.first = n * 2;
	cur.second = dp[n * 2][0].first > dp[n * 2][1].first ? 0 : 1;
	while (cur.first > 0) {
		tmax[cur.first] = cur.second;
		cur.second = dp[cur.first][cur.second].second;
		cur.first--;		
	}
	return 1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n; 
	for (int i = 1; i <= n * 2; ++i)
		cin >> a[i];
	for (int i = 1; i <= n * 2; ++i)
		cin >> b[i];
	a[n*2 + 1] = b[n*2 + 1] = 2e9;
	
	// 1 la dung A, 0 la dung B
	if (!trace_min() || !trace_max()) {
		swap(a, b);
		if (!trace_min() || !trace_max())
			return cout << -1, 0;
		for (int i = 1; i <= n*2; ++i)
			tmin[i] = !tmin[i], tmax[i] = !tmax[i];
	}
	
	vector<pair<int, int>> seg;
	for (int i = 1; i <= n*2; ++i) if (tmin[i] == 0 && tmax[i] == 1) {
		int j = i;
		while (j <= n*2 && tmin[j] == 0 && tmax[j] == 1) j++;
		j--; seg.emplace_back(i, j); i = j;
	}
	sort(seg.begin(), seg.end(), [&](pair<int, int>& u, pair<int, int>& v) {
		return u.second - u.first < v.second - v.first;
	});
	 	
	for (int i = 1; i <= n * 2; ++i)
		res[i] = tmin[i];
		
	int cur = n;
	for (auto& s : seg) {
		if (s.second - s.first + 1 <= cur) {
			cur -= s.second - s.first + 1;
			for (int i = s.first; i <= s.second; ++i) res[i] = 1;
		} else {
			for (int i = s.first; i <= s.second; ++i) {
				if (a[i] <= b[i + 1]) {
					res[i] = 1; cur--;
					if (cur == 0) break;
					continue;
				} else {
					while (a[i] > b[i + 1]) i++;
					for (int j = i; !res[j]; --j) {
						res[j] = 1; cur--;
						if (cur == 0) break;
					} 
				}
			}
		}
		if (cur == 0) break;
	}
//	for (int i = 1; i <= n*2; ++i)
//		cout << (tmin[i] == 1 ? 'A' : 'B');
//	cout << '\n';
//	for (int i = 1; i <= n*2; ++i)
//		cout << (tmax[i] == 1 ? 'A' : 'B');
//	cout << '\n';
	for (int i = 1; i <= n*2; ++i)
		cout << (res[i] == 1 ? 'A' : 'B');
	
	return 0;
}


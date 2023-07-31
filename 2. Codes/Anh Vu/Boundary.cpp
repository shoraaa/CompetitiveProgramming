#include <bits/stdc++.h>
using namespace std;

int64_t n, m;
int check(int64_t x) {
	if ((n - 1) % x == 0 && (m - 1) % x == 0) return 1;
	if ((n - 2) % x == 0 && m % x == 0) return 1;
	if ((m - 2) % x == 0 && n % x == 0) return 1;
	if ((n - 1) % x == 0 && (m - 2) % x == 0 && m % x == 0) return 1;
	if ((m - 1) % x == 0 && (n - 2) % x == 0 && n % x == 0) return 1;
	
	return 0;
}
void solve() {
	cin >> n >> m; int64_t p = 2 * (n + m) - 4;
	vector<int64_t> res;
	for (int64_t i = 1; i * i <= p; ++i) {
		if (check(i)) 
			res.push_back(i);
		if (i * i != p && check(p / i))
 			res.push_back(p / i);
 	}	
	sort(res.begin(), res.end());
	cout << res.size() << ' ';
	for (int64_t &v : res) cout << v << ' ';
	cout << '\n'; 
}
signed main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);	
	int T; cin >> T;
	while (T--) 
	  solve();
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "harvest";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int n, m;
const ll oo = 1e18;
const int N = 1e5 + 5;
ll a[N], b[N];
ll cost(ll l, ll r, ll p) {
	return r - l + min(abs(r - p), abs(l - p));
}
int check(ll t) {
	// dp[i] = j la khom hoa xa nhat xet den con thu i
	int cur = 0;
	for (int i = 1; i <= m; ++i) {
		int nxt = cur + 1;
		while (nxt <= n && cost(a[cur + 1], a[nxt], b[i]) <= t) nxt++;
		cur = nxt - 1;
	}
	return cur == n;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	while (cin >> m >> n) {
		if (m == 0) break;
		for (int i = 1; i <= m; ++i)
			cin >> b[i];
		for (int i = 1; i <= n; ++i)
			cin >> a[i];
		sort(a + 1, a + n + 1);
		sort(b + 1, b + m + 1);
		ll lo = 0, hi = 1e12, mid, ans = 1e12;
		while (lo <= hi) {
			mid = (lo + hi) >> 1;
			if (check(mid)) 
				ans = mid, 
				hi = mid - 1;
			else 
				lo = mid + 1;
		}
		cout << ans << ' ';
	}
	return 0;
}


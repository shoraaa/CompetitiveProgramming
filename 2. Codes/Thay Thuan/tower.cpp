#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct S {
	int x, y, h;
	S(int x, int y, int h): x(x), y(y), h(h) {}
	bool operator < (const S& s) const {
		if (x == s.x) return y > s.y;
		return x > s.x;
	}
};
const int N = 1000 * 6 + 5;
vector<S> a;
pair<ll, int> dp[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n; a.reserve(6 * n);
	for (int i = 0, x, y, h; i < n; ++i) {
		cin >> x >> y >> h;
		a.emplace_back(x, y, h);
		a.emplace_back(y, x, h);
		a.emplace_back(x, h, y);
		a.emplace_back(h, x, y);
		a.emplace_back(y, h, x);
		a.emplace_back(h, y, x);
	}
	n *= 6;
	sort(a.begin(), a.end());
	pair<ll, int> res = {0, 0};
	for (int i = 0; i < n; ++i) {
		dp[i] = {a[i].h, -1};
		for (int j = i-1; ~j; --j) if (a[i].x < a[j].x && a[i].y < a[j].y)
			dp[i] = max(dp[i], {dp[j].first + a[i].h, j});
		res = max(res, {dp[i].first, i});
	}
	cout << res.first << ' ';
	stack<int> st;
	for (int i = res.second; i != -1; i = dp[i].second) 
		st.emplace(i);
	cerr << st.size() << '\n';
	while (!st.empty()) {
		int u = st.top(); st.pop();
		cout << a[u].x << ' ' << a[u].y << ' ' << a[u].h << '\n';
	}
	return 0;
}


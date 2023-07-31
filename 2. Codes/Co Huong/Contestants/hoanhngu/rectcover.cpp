#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<class X, class Y>
void cmax(X &x, const Y &y) {
   if (x < y) x = y;
}

template<class X, class Y>
void cmin(X &x, const Y &y) {
   if (x > y) x = y;
}

const int MAXN = 103, MAXA = 3e6 + 5, inf = 1e9 + 7;
int dp[MAXN][MAXN][MAXN], highest[MAXA];
vector<pair<int, int>> xet;
int sizeHeight, n, square;
vector<int> val;

int calc(int l, int r, int h) {
   if (h == sizeHeight) return 0;
   int &cur = dp[l][r][h];
   if (cur != -1) return cur;
   cur = inf;
   bool valid = false;
   for (int i = l; i <= r; i++)
      valid |= xet[i].second == h;
   if (!valid) return cur = calc(l, r, h + 1);
   for (int i = h; i < sizeHeight; i++) {
      bool valid = 1ll * (xet[r].first - xet[l].first) * val[i] <= (ll)square;
      if (!valid) continue;
      cmin(cur, calc(l, r, i + 1) + 1);
   }
   for (int i = l; i < r; i++)
      cmin(cur, calc(l, i, h) + calc(i + 1, r, h));
   return cur;
}

int32_t main() {
	cin.tie(0) -> sync_with_stdio(0);
	if (fopen("rectcover.in", "r")) {
		freopen("rectcover.in", "r", stdin);
		freopen("rectcover.out", "w", stdout);
	}
	cin >> n >> square;
	for (int i = 1; i <= n; i++) {
		int x, y; cin >> x >> y;
		cmax(highest[x], y);
	}
	for (int i = 0; i <= (int)3e6; i++) {
		if (!highest[i]) continue;
		val.emplace_back(highest[i]);
	}
	sort(val.begin(), val.end());
	val.resize(unique(val.begin(), val.end()) - val.begin());
	sizeHeight = val.size();
	for (int i = 0; i <= (int)3e6; i++) {
		if (!highest[i]) continue;
		xet.emplace_back(i, lower_bound(val.begin(), val.end(), highest[i]) - val.begin());
	}
	memset(dp, -1, sizeof dp);
	cout << calc(0, xet.size() - 1, 0);
}
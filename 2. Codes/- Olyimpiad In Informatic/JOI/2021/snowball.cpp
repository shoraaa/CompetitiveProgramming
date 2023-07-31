#include<bits/stdc++.h>
#define print(_v) for (auto& _e : _v) {cerr << _e << ' ';} cerr << '\n';
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
ll a[N], b[N], p[N], res[N];
int n, q;
vector<pair<ll, ll>> c;
void pre_calc() {
	for (int i = 1; i <= q; ++i)
		p[i] = p[i-1] + b[i];
	vector<ll> pos, neg;
	if (p[1] >= 0) neg.emplace_back(0);
	bool flag = 0;
	for (int i = 1; i <= q;) {
		int j = i; ll v = 0;
		if (p[i] >= 0) {
			while (j <= q && p[j] >= 0) v = max(v, p[j]), j++;
			pos.emplace_back(v);
		} else {
			while (j <= q && p[j] <= 0) v = min(v, p[j]), j++;
			neg.emplace_back(v);
			if (j == q + 1) flag = 1;
		}
		i = j;
	}
	c.clear();
	ll cur = 0;
	for (int i = 0; i < pos.size(); ++i) {
		cur = min(cur, neg[i]);
		if (c.empty() || pos[i] > c.back().first) 
			c.emplace_back(pos[i], cur);
	}
	if (flag) c.emplace_back(pos.empty() ? 0 : pos.back(), min(cur, neg.back()));
}
ll val(int i, int j) {
	return min(c[j].first, a[i+1] - a[i] + c[j].second);
}
int check(int i, int j) {
	return (j == 0 || val(i, j) > val(i, j-1)) 
			&& (val(i, j) >= val(i, j+1));
}
void solve(int f = 0) {
	// tim dinh cua day min(c[i].first, D + c[i].second) voi moi D
	for (int i = 1; i <= n; ++i) {
		if (c.size() == 1) {
			res[f ? n-i+1 : i] += max(0LL, val(i, 0)); continue;
		}
		int lo = 0, hi = int(c.size()) - 3, mid, 
		ans = val(i, c.size() - 1) > val(i, c.size() - 2) ? c.size() - 1 : c.size() - 2; 
		while (lo <= hi) {
			mid = (lo + hi) >> 1;
			if (check(i, mid))	
				ans = mid, lo = hi + 1;
			else if (val(i, mid) < val(i, mid + 1))
				lo = mid + 1;
			else 
				hi = mid - 1;
		}
		res[f ? n-i+1 : i] += max(0LL, val(i, ans));
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	// min(pre[i], D - min[i])
	// -> day tang roi giam
	cin >> n >> q;
	a[n + 1] = 1e18;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 1; i <= q; ++i)
		cin >> b[i];
	pre_calc();
	solve();
	for (int i = 1; i <= n; ++i)
		a[i] = -a[i];
	reverse(a + 1, a + n + 1);
	for (int i = 1; i <= q; ++i)
		b[i] = -b[i];
	pre_calc();
	solve(1);
	for (int i = 1; i <= n; ++i)
		cout << res[i] << '\n';
	return 0;
}


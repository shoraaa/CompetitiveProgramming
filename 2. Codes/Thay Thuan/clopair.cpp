#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
struct P {
	int x, y, i;
	P(int x, int y, int i): x(x), y(y), i(i) {}
	bool operator < (const P& p) const {
		if (x == p.x) return y < p.y;
		return x < p.x;
	}
};
vector<P> a;
int n;
ll sqr(ll x) {
	return x * x;
}
ld distance(P& u, P& v) {
	return sqrt(sqr(u.x - v.x) + sqr(u.y - v.y));
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n; a.reserve(n);
	for (int i = 0, x, y; i < n; ++i)
		cin >> x >> y, a.emplace_back(x, y, i);
	sort(a.begin(), a.end());
	set<P> near;
	pair<ld, pair<int, int>> res; res.first = 1e15;
	for (int i = 0; i < n; ++i) {
		while (!near.empty() && near.begin()->x < a[i].x - res.first) near.erase(near.begin());
		for (P p : near) 
			res = min(res, {distance(p, a[i]), {p.i, a[i].i}});
		near.insert(a[i]);
	}
	if (res.second.first > res.second.second) swap(res.second.first, res.second.second);
	cout << res.second.first << ' ' << res.second.second << ' ' << fixed << setprecision(6) << res.first;
	return 0;
}


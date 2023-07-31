#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, inf = 1e9 + 9;

int n, k; 
pair<int, int> a[N];
#define fi first
#define se second

ll res = 1e18;

namespace task1 {
	void solve() {
		int xn = inf, xx = -inf, yn = inf, yx = -inf;
		for (int i = 1; i <= n; ++i) {
			xn = min(xn, a[i].fi), xx = max(xx, a[i].fi);
			yn = min(yn, a[i].se), yx = max(yx, a[i].se);
		}
		ll l = max(xx - xn, yx - yn); l = max(l, 1ll);
		res = min(res, l * l);
	}
}

namespace task2 {
	int px[N], pn[N];
	void solve() {
		int t = 2; 
		while (t--) {
			sort(a + 1, a + n + 1);
			for (int i = n + 1; i >= 1; --i) 
			  px[i] = -inf, pn[i] = inf;
			for (int i = n; i >= 1; --i) {
				px[i] = max(px[i + 1], a[i].se);
				pn[i] = min(pn[i + 1], a[i].se);
			}
			int sx = -inf, sn = inf;
			for (int i = 1; i <= n; ++i) {
				int j = i;
				while (j <= n && a[j].fi == a[i].fi) {
					sx = max(sx, a[j].se); sn = min(sn, a[j].se); j++;
				}
				i = j - 1;
				if (i + 1 <= n) {
					ll l = max(a[i].fi - a[1].fi, sx - sn), 
						 r = max(a[n].fi - a[i + 1].fi, px[i + 1] - pn[i + 1]);
					l = max(l, 1ll); r = max(r, 1ll);
					res = min(res, max(l * l, r * r));
				}
			}
			for (int i = 1; i <= n; ++i) swap(a[i].fi, a[i].se);
		}
	}
}


struct SegmentTree {
	int n;
	vector<int> max_val, min_val;
	SegmentTree() {}
	SegmentTree(int n) : n(n) {
		max_val.resize(4 * n + 4, -inf);
		min_val.resize(4 * n + 4, inf);
	}
	void update(int id, int l, int r, int x, int v) {
		if (l > x || r < x) return;
		if (l == r) 
			return max_val[id] = max(max_val[id], v), min_val[id] = min(min_val[id], v), void();
		int mid = (l + r) / 2;
		update(2 * id, l, mid, x, v), update(2 * id + 1, mid + 1, r, x, v);
		max_val[id] = max(max_val[2 * id], max_val[2 * id + 1]);
		min_val[id] = min(min_val[2 * id], min_val[2 * id + 1]);
	}
	int vx, vn;
	void get(int id, int l, int r, int u, int v) {
		if (l > v || r < u) return;
		if (u <= l && r <= v) 
			return vx = max(vx, max_val[id]), vn = min(vn, min_val[id]), void();
		int mid = (l + r) / 2;
		get(2 * id, l, mid, u, v); 
		get(2 * id + 1, mid + 1, r, u, v);
	}
	void update(int p, int v) {
		update(1, 1, n, p, v);
	}
	int get(int l, int r) {
		vx = -inf; vn = inf;
		get(1, 1, n, l, r);		
		return vx - vn;
	}
};

namespace task3 {
	ll S(int x, int y) {
		ll l = max({x, y, 1});
		return l * l;
	}
	void task1() {
		int t = 2; 
		while (t--) {
			sort(a + 1, a + n + 1);
			SegmentTree st(n);
			for (int i = 1; i <= n; ++i) st.update(i, a[i].se);
			for (int i = 1; i <= n - 2; ++i) {
				int lo = i + 1, hi = n - 1;
				ll ans1 = 1e18, ans2 = 1e18;
				while (lo <= hi) {
					int mi = (lo + hi) / 2;
					ll s1 = S(a[mi].fi - a[i + 1].fi, st.get(i + 1, mi)),
						 s2 = S(a[n].fi - a[mi + 1].fi, st.get(mi + 1, n));
					if (s1 <= s2) ans1 = s2, lo = mi + 1;
					else hi = mi - 1;					
				}
				lo = i + 1, hi = n - 1;
				while (lo <= hi) {
					int mi = (lo + hi) / 2;
					ll s1 = S(a[mi].fi - a[i + 1].fi, st.get(i + 1, mi)),
						 s2 = S(a[n].fi - a[mi + 1].fi, st.get(mi + 1, n));
					if (s1 >= s2) ans2 = s1, hi = mi - 1;
					else lo = mi + 1;					
				}
				res = min(res, max(S(a[i].fi - a[1].fi, st.get(1, i)), min(ans1, ans2)));
			}
			for (int i = 1; i <= n; ++i) swap(a[i].fi, a[i].se);
		}
	}
	ll suf[N]; int p[N], c[N];
	void task2() {
		int q = 2; 
		while (q--) {
			int t = 2; 
			while (t--) {
				sort(a + 1, a + n + 1);
				iota(c + 1, c + n + 1, 1);
				sort(c + 1, c + n + 1, [&](int &x, int &y) {
					return a[x].se < a[y].se;
				});
				for (int i = 1; i <= n; ++i) p[c[i]] = i;
				SegmentTree st1(n), st2(n);
				for (int i = n; i >= 1; --i) {
					suf[i] = 1e18; 
					st1.update(p[i], a[i].fi);
					st2.update(p[i], a[i].se);
					int lo = 1, hi = n - 1; 
					ll ans1 = inf, ans2 = inf;
					while (lo <= hi) {
						int mi = (lo + hi) / 2;
						ll s1 = S(st1.get(1, mi), st2.get(1, mi)),
							 s2 = S(st1.get(mi + 1, n), st2.get(mi + 1, n));
						if (s1 <= s2) ans1 = s2, lo = mi + 1;
						else hi = mi - 1;
					}
					lo = 1, hi = n - 1;
					while (lo <= hi) {
						int mi = (lo + hi) / 2;
						ll s1 = S(st1.get(1, mi), st2.get(1, mi)),
							 s2 = S(st1.get(mi + 1, n), st2.get(mi + 1, n));
						if (s1 >= s2) ans2 = s1, hi = mi - 1;
						else lo = mi + 1;
					}
					suf[i] = min(ans1, ans2);
				}
				int sx = -inf, sn = inf;
				for (int i = 1; i <= n - 2; ++i) {
					sx = max(sx, a[i].se); sn = min(sn, a[i].se);
					res = min(res, max(S(sx - sn, a[i].fi - a[1].fi), suf[i + 1]));
				}
				reverse(a + 1, a + n + 1);
			}
			for (int i = 1; i <= n; ++i) swap(a[i].fi, a[i].se);
		}
	}
	void solve() {
		task1(); task2(); 
	}
}

signed main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);	
	
	if (fopen("ksquare.inp", "r"))
		freopen("ksquare.inp", "r", stdin),
		freopen("ksquare.out", "w", stdout);
		
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cin >> a[i].fi >> a[i].se;
		
	if (k >= 1) task1::solve();
	if (k >= 2) task2::solve();
	if (k >= 3) task3::solve();
	
	cout << res;
	return 0;
}
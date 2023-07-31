#include <bits/stdc++.h>
using namespace std;

#define print(_v) for (auto &_ : _v) {cerr << _ << ' ';} cerr << '\n';
using ll = long long;
using ld = long double;
random_device dev;
mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
#define NguyenLuong "b6"
const int N = 2e5 + 5;
const int VAL = 1e6 + 5;
int n, q, a[N];
int Max[VAL];
ll bit[N];
int p[VAL];
set<int> pos;

void sieve() {
	for (int i = 1; i <= 1e6; ++i)
		Max[i] = i;
	for (int i = 2; i * i <= 1e6; ++i) {
		if (Max[i] == i) {
			for (int j = 2 * i; j <= 1e6; j += i)
				Max[j] = i;
		}
	}
}

int phi(int n) {
	int ans = n;
	while (n != 1) {
		ans /= Max[n];
		ans *= (Max[n] - 1);
		int x = Max[n];
		while (n % x == 0) n /= x;
	}
	return ans;
}

//int phi(int n) {
//	int ans = n;
//	for (int i = 2; i * i <= n; ++i) {
//		if (n % i == 0) {
//			ans /= i;
//			while (n % i == 0) n /= i;
//			ans *= (i - 1);
//		}
//	}
//	if (n != 1) ans /= n, ans *= (n - 1);
//	return ans;
//}

void upd(int i, int val) {
	for (; i <= n; i += i & -i)
		bit[i] += val;
}

ll get(int i) {
	ll ans = 0;
	for (; i; i -= i & -i)
		ans += bit[i];
	return ans;
}

void solve() {
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	
	sieve();
	
	for (int i = 1; i <= n; ++i)
		if (a[i] != 1) pos.insert(i);
	pos.insert(n + 1);
	
	for (int i = 1; i <= n; ++i)
		upd(i, a[i]);
	
	for (int i = 1; i <= 1e6; ++i)
		p[i] = phi(i);
	
	while (q--) {
		int t; cin >> t;
		if (t == 1) {
			int l, r; cin >> l >> r;
			
			int x = n + 1;
			auto it = pos.lower_bound(l);
			while (it != pos.end() && *it <= r) {
				int i = *it;
				int val = p[a[i]];
				upd(i, val - a[i]);
				a[i] = val;
				if (a[i] == 1) it = pos.erase(it);
				else it++;
			}
		} else if (t == 2) {
			int l, r; cin >> l >> r;
			if (l == r) cout << a[l] << '\n';
			else cout << get(r) - get(l - 1) << '\n';
		} else {
			int p, v; cin >> p >> v;
			if (a[p] == 1 && v != 1) pos.insert(p);
			else if (a[p] != 1 && v == 1) pos.erase(p);
			upd(p, v - a[p]);
			a[p] = v;
		}
	}
}

int main() {
    ios::sync_with_stdio(0);
    cout.tie(0); cin.tie(0);
    if (fopen(NguyenLuong".inp", "r")) {
        freopen(NguyenLuong".inp", "r", stdin);
        freopen(NguyenLuong".out", "w", stdout);
    }
    solve();
    return 0;
}

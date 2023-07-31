#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll cal(ll l, ll t, ll d) {
	return t * (l * 2 + (t - 1) * d) / 2;
}

void solve() {
	ll l, r; cin >> l >> r;
	bool sw = 0;
	if (l > r) {
		swap(l, r); sw = 1;
	}
	ll lo = 0, hi = 2e9, res = 0;
	while (lo <= hi) {
		ll mi = (lo + hi) / 2;
		if (cal(1, mi, 1) <= r - l) {
			res = mi; lo = mi + 1;
		}
		else hi = mi - 1;
	}
	r -= cal(1, res, 1);
	if (l == r) sw = 1;
	ll addl = 0, addr = 0;
	lo = 0; hi = 2e9;
	while (lo <= hi) {
		ll mi = (lo + hi) / 2;
		if (cal(res + 2, mi, 2) <= l) {
			addl = mi; lo = mi + 1;
		}
		else hi = mi - 1;
	}
	lo = 0; hi = 2e9;
	while (lo <= hi) {
		ll mi = (lo + hi) / 2;
		if (cal(res + 1, mi, 2) <= r) {
			addr = mi; lo = mi + 1;
		}
		else hi = mi - 1;
	}
	l -= cal(res + 2, addl, 2);
	r -= cal(res + 1, addr, 2);
	res += addl + addr;
	if (sw) swap(l, r);
	cout << res << ' ' << l;
	cout << ' ' << r << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int t; cin >> t;
	while (t--) solve();
}
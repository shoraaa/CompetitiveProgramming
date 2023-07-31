#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
ll a[N], riu[N];
struct Q {
	ll l;
	int p, i, prev = -1, pr_rev = -1;
	Q(ll p, ll l, int i, int prev = -1, int pr_rev = -1): p(p), l(l), i(i), prev(prev), pr_rev(pr_rev) {}
};
int n, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	vector<ll> c(n);
	for (int i = 0; i < n; ++i) 
		cin >> a[i], c[i] = a[i];
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	for (int i = 0; i < n; ++i) {
		int j = lower_bound(c.begin(), c.end(), a[i]) - c.begin();
		riu[j] = i;
	}
	n = c.size();
	vector<Q> cur, nxt;
	cin >> q;
	for (int i = 0, p, l; i < q; ++i) {
		cin >> p >> l, p--;
		p = lower_bound(c.begin(), c.end(), a[p]) - c.begin();
		cur.emplace_back(p, l, i);
	}
	for (int r = 0, phai = 1; r <= 50; ++r, phai ^= 1) {
		nxt.clear();
		if (phai) {
			// tim dinh lon nhat <= xi + li
			for (auto& qr : cur) {
				int j = upper_bound(c.begin(), c.end(), c[qr.p] + qr.l) - c.begin() - 1;
				nxt.emplace_back(j, qr.l - (c[j] - c[qr.p]), qr.i, qr.p, qr.prev);
			}
		} else {
			// tim dinh nho nhat >= xi - li
			for (auto& qr : cur) {
				int j = lower_bound(c.begin(), c.end(), c[qr.p] - qr.l) - c.begin();
				nxt.emplace_back(j, qr.l - (c[qr.p] - c[j]), qr.i, qr.p, qr.prev);
			}
		}
		nxt.swap(cur);
	}
	// dang quay sang phai
	for (auto& qr : cur) if (qr.p == qr.pr_rev && qr.p != qr.prev) {
		ll cnt = qr.l / abs(c[qr.p] - c[qr.prev]);
		if (cnt & 1) qr.p = qr.prev;
	}
	vector<int> res(q);
	for (auto& qr : cur) 
		res[qr.i] = qr.p;
	for (int i = 0; i < q; ++i)
		cout << riu[res[i]] + 1 << '\n';
		
	return 0;
}


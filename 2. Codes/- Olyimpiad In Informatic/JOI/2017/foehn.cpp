#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2e5 + 5; 
int a[N];
int n, q, S, T;
struct V {
	int greater = 0, equal_or_less = 0;
	ll first = 0, last = 0;
	ll res = 0, lazy = 0;
	void add(ll v) {
		lazy += v, first += v, last += v;
	}
};
V merge(V& x, V& y) {
	V z;
	z.first = x.first, z.last = y.last;
	z.res = x.res + y.res, 
	z.greater = x.greater + y.greater, 
	z.equal_or_less = x.equal_or_less + y.equal_or_less;
	if (y.first > x.last) z.res -= S * (y.first - x.last), z.greater++;
	else z.res += T * (x.last - y.first), z.equal_or_less++;
	return z;
}
struct segment_tree {
	vector<V> st;
	int n, x, y, v;
	segment_tree(int n): n(n), st((n + 1) << 2) {
		build(1, 0, n);
	}
	void push(int k) {
		st[k << 1].add(st[k].lazy);
		st[k << 1 | 1].add(st[k].lazy);
		st[k].lazy = 0;
	}
	void build(int k, int l, int r) {
		if (l == r) 
			return st[k].first = st[k].last = a[l], void();
		int m = (l + r) >> 1;
		build(k << 1, l, m);
		build(k << 1 | 1, m+1, r);
		st[k] = merge(st[k << 1], st[k << 1 | 1]);
	}
	void add(int k, int l, int r) {
		if (l > y || r < x) return;
		if (l >= x && r <= y) 
			return st[k].add(v), void();
		int m = (l + r) >> 1;
		push(k);
		add(k << 1, l, m);
		add(k << 1 | 1, m+1, r);
		st[k] = merge(st[k << 1], st[k << 1 | 1]);
	}
	ll get(int l, int r, int val) {
		x = l, y = r, v = val;
		add(1, 0, n);
		return st[1].res;
	}
};
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> q >> S >> T;
	for (int i = 0; i <= n; ++i)
		cin >> a[i];
	segment_tree st(n);
	for (int i = 0, l, r, v; i < q; ++i) {
		cin >> l >> r >> v;
		cout << st.get(l, r, v) << '\n';
	}
	return 0;
}


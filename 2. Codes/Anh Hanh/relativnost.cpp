#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "relativnost";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5, K = 20, M = 1e4 + 7;
inline int sum(int x, int y) {
	x += y; if (x >= M) x -= M; return x;
}
int a[N], b[N];
int k;
struct segment_tree {
	struct node {
		array<int, K> c;
		int all;
		void merge(array<int, K>& u, array<int, K>& v) {
			for (int i = 0; i < k; ++i)
				c[i] = 0;
			for (int i = 0; i < k; ++i)
				for (int j = 0; j <= i; ++j)
					c[i] += u[j] * v[i-j];
			for (int i = 0; i < k; ++i)
				c[i] %= M;
		}
	};
	int n, x;
	vector<node> st;
	segment_tree(int n): n(n), st(n * 2 - 1) { build(0, 0, n-1); }
	void build(int k, int l, int r) {
		if (l == r) 
			return st[k].c[0] = b[l], st[k].c[1] = a[l], 
						 st[k].all = sum(a[l], b[l]), void();
		int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
		build(lc, l, m), build(rc, m+1, r);
		st[k].merge(st[lc].c, st[rc].c);
		st[k].all = st[lc].all * st[rc].all % M;
	}
	void update(int k, int l, int r) {
		if (l == r) 
			return st[k].c[0] = b[l], st[k].c[1] = a[l], 
						 st[k].all = sum(a[l], b[l]), void();
		int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
		if (x <= m) update(lc, l, m);
		else update(rc, m+1, r);
		st[k].merge(st[lc].c, st[rc].c);
		st[k].all = st[lc].all * st[rc].all % M;
	}
	void update(int p) {
		x = p, update(0, 0, n-1);
	}
};
int n, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> a[i], a[i] %= M;
	for (int i = 0; i < n; ++i)
		cin >> b[i], b[i] %= M;
	segment_tree st(n);
	cin >> q;
	for (int i = 0, p, x, y; i < q; ++i) {
		cin >> p >> x >> y, p--, x %= M, y %= M;
		a[p] = x, b[p] = y, st.update(p);
		int res = st.st[0].all;
		for (int i = 0; i < k; ++i)
			res -= st.st[0].c[i];
		cout << (res % M + M) % M << ' ';
	}
	return 0;
}
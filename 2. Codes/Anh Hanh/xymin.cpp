#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "xymin";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2000 + 5;
int a[N];
pair<int, int> b[N];
struct segment_tree {
	struct node {
		int erased, min;
	};
	int n, x, y, res, erased;
	vector<node> st;
	segment_tree(int n): n(n), st(n * 2 - 1) { build(0, 0, n-1); }
	void build(int k, int l, int r) {
		if (l == r) 
			return st[k].min = a[l], void();
		int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
		build(lc, l, m), build(rc, m+1, r);
		st[k].min = min(st[lc].min, st[rc].min);
	}
	void erase(int k, int l, int r) {
		if (l == r) 
			return st[k].min = 1e9, st[k].erased = 1, void();
		int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
		if (x <= m) erase(lc, l, m);
		else erase(rc, m+1, r);
		st[k].min = min(st[lc].min, st[rc].min);
		st[k].erased = st[lc].erased + st[rc].erased;
	}
	
	void get(int k, int l, int r) {
		if (l > y || r < x) return;
		if (l >= x && r <= y)
			return res = min(res, st[k].min), erased += st[k].erased, void();
		int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
		get(lc, l, m), get(rc, m+1, r);
	}
	
	int get(int l, int r) {
		x = l, y = r, res = 1e9, erased = 0;
		get(0, 0, n-1);
		return res;
	}
	int get(int i) {
		int lo, hi, mid, l = i, r = i;
		lo = 0, hi = i;
		while (lo <= hi) {
			mid = lo + hi >> 1;
			if (get(mid, i) >= a[i]) 
				l = mid, 
				hi = mid - 1;
			else
				lo = mid + 1;
		}
		lo = i, hi = n-1;
		while (lo <= hi) {
			mid = lo + hi >> 1;
			if (get(i, mid) >= a[i]) 
				r = mid, 
				lo = mid + 1;
			else
				hi = mid - 1;
		}
		get(l, r);
		return r - l + 1 - erased;
	}
	void erase(int i) {
		x = i; erase(0, 0, n-1);
	}
};
int n, k, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n >> k >> q; q = min(q, n - k + 1);
	for (int i = 0; i < n; ++i)
		cin >> a[i], b[i].first = a[i], b[i].second = i;
	sort(b, b + n);
	vector<pair<int, int>> s;
	for (int i = 0; i < n - q + 1; ++i)
		s.emplace_back(b[i + q - 1].first - b[i].first, i);
	sort(s.begin(), s.end());
	for (auto& p : s) {
		int l = p.second, r = l + q - 1;
		bool can_erase = 1;
		segment_tree st(n);
		for (int i = l; i <= r; ++i) {
			if (st.get(b[i].second) < k) {
				can_erase = 0;
				break;
			}
			st.erase(b[i].second);
		}
		if (!can_erase) continue;
		return cout << p.first, 0;
	}
	return 0;
}


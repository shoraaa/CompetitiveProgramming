#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct S {
	int x, y, i;
	S(int x, int y, int i): x(x), y(y), i(i) {}
	bool operator < (const S& s) const {
		if (x == s.x) return y > s.y;
		return x < s.x;
	}
};
struct segment_tree {
	int n, res, x, y, v;
	vector<int> st;
	segment_tree(int n): n(n), st(n * 4) {}
	void get(int k, int l, int r) {
		if (l > y || r < x) return;
		if (l >= x && r <= y) 
			return res = max(res, st[k]), void();
		int m = (l + r) >> 1;
		get(k << 1, l, m);
		get(k << 1 | 1, m + 1, r);
	}
	void update(int k, int l, int r) {
		if (l > x || r < x) return;
		if (l == r) 
			return st[k] = max(st[k], v), void();
		int m = (l + r) >> 1;
		update(k << 1, l, m);
		update(k << 1 | 1, m + 1, r);
		st[k] = max(st[k << 1], st[k << 1 | 1]);
	}
	int get(int p) {
		x = p, y = n-1, res = 0, get(1, 0, n-1);
		return res;
	}
	void update(int p, int vl) {
		x = p, v = vl, update(1, 0, n-1);
	}
};
const int N = 1e5 + 5;
int dp[N], ly[N];
vector<S> a;
vector<int> cy;
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 0, x, y; i < n; ++i)
		cin >> x >> y, 
		cy.emplace_back(y),
		a.emplace_back(x, y, i);
	sort(a.begin(), a.end());
	sort(cy.begin(), cy.end());
	cy.erase(unique(cy.begin(), cy.end()), cy.end());
	segment_tree st(cy.size());
	vector<vector<int>> res;
	for (int i = 0; i < n; ++i) {
		int py = lower_bound(cy.begin(), cy.end(), a[i].y) - cy.begin();
		int j = st.get(py);
		if (j == res.size()) 
			res.emplace_back();
		res[j].emplace_back(a[i].i + 1);
		st.update(py, j + 1);
	}
	cout << res.size() << '\n';
	for (auto arr : res) {
		cout << arr.size() << ' ';
		for (int i : arr) cout << i << ' ';
		cout << '\n';
	}
	return 0;
}


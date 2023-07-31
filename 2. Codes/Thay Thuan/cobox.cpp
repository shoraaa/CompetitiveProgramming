#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
struct S {
	int h, w, i;
	S(int h = 2e9, int w = 2e9, int i = 0): h(h), w(w), i(i) {}
	bool operator < (const S& s) const {
		if (h == s.h) return w < s.w;
		return h > s.h;
	}
};
vector<S> a;
vector<int> c, d;
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n; a.reserve(n);
	for (int i = 0, h, w; i < n; ++i) 
		cin >> h >> w, 
		a.emplace_back(h, w, i + 1);
	auto cmp = [&](const S& u, const S& v) {
		return u.w <= v.w || u.h <= v.h;
	};
	sort(a.begin(), a.end());
	// tim so day tang it nhat co the chia trong day
	vector<S> b(n);
	vector<vector<int>> res;
	for (int i = 0; i < n; ++i) {
		int k = lower_bound(b.begin(), b.end(), a[i], cmp) - b.begin();
		if (k == res.size()) res.emplace_back();
		b[k] = a[i];
		res[k].emplace_back(a[i].i);
	}
	cout << res.size() << '\n';
	for (auto& d : res) {
		cerr << d.size() << ' ';
		for (int i : d) cout << i << ' ';
		cout << '\n';
	}
	
	return 0;
}


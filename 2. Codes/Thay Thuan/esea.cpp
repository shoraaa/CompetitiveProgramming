#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct S {
	int x1, y1, x2, y2, i;
	S(int x1, int y1, int x2, int y2, int i): x1(x1), y1(y1), x2(x2), y2(y2), i(i) {}
	bool operator < (const S& s) const {
		if (x1 != s.x1) return x1 < s.x1;
		if (y1 != s.y1) return y1 < s.y1;
		if (x2 != s.x2) return x2 < s.x2;
		return y2 < s.y2;
	}
};
struct indexed_set : map<int, int> {
	void update(int x, int v) {
		auto it = upper_bound(x);
		if (it != begin()) {
			it--;
			if (it->second >= v) return;
		}
		for (it = lower_bound(x); it != end();) {
			if (it->second > v) break;
			it = erase(it);
		}
		insert({x, v});
	}
	int get(int x) {
		auto it = upper_bound(x); 
		if (it == begin()) return 0;
		it--;
		return it->second;
	}
};
struct segment_tree {
	int n, res, x, y, p, v;
	vector<indexed_set> st;
	segment_tree(int n): n(n), st(n * 4) {}
	void get(int k, int l, int r) {
		if (l > y || r < x) return;
		if (l >= x && r <= y) 
			return res = max(res, st[k].get(p)), void();
		int m = (l + r) >> 1;
		get(k << 1, l, m);
		get(k << 1 | 1, m + 1, r);
	}
	void update(int k, int l, int r) {
		if (l > x || r < x) return;
		if (l == r) 
			return st[k].update(p, v), void();
		int m = (l + r) >> 1;
		update(k << 1, l, m);
		update(k << 1 | 1, m + 1, r);
		st[k].update(p, v);
	}
	int get(int pos, int y1) {
		if (pos == -1) return 0;
		p = y1, x = 0, y = pos, res = 0, get(1, 0, n-1);
		return res;
	}
	void insert(int pos, int y2, int val) {
		x = pos, p = y2, v = val, update(1, 0, n-1);
	}
};
int n;
void read(int& result){
	bool minus = false;
	result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch - '0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result * 10 + (ch - '0');
	}
	if (minus) result = -result;
}

inline void write(int x) {
  if (x > 9) write(x / 10);
  putchar(x % 10 + 48);
}
vector<S> a;
vector<int> cx;
vector<vector<int>> res;
int main() {
	int T;
	read(T);
	while (T--) {
		read(n); cx.clear(); a.clear();
		a.reserve(n), cx.reserve(n); res.reserve(n);
		for (int i = 0, x1, y1, x2, y2; i < n; ++i) {
			read(x1); read(y1); read(x2); read(y2);
			cx.emplace_back(x2),
			a.emplace_back(x1, y1, x2, y2, i);
		}
		sort(a.begin(), a.end());
		sort(cx.begin(), cx.end());
		cx.erase(unique(cx.begin(), cx.end()), cx.end());
		segment_tree st(cx.size());
		res.clear();
		for (int i = 0; i < n; ++i) {
			int x1 = lower_bound(cx.begin(), cx.end(), a[i].x1) - cx.begin();
			int cur = st.get(x1 - 1, a[i].y1 - 1);
			
			if (cur == res.size()) 
				res.emplace_back();
			res[cur].emplace_back(a[i].i + 1);
			
			int x2 = lower_bound(cx.begin(), cx.end(), a[i].x2) - cx.begin();
			st.insert(x2, a[i].y2, cur + 1);
		}
		write(res.size());
		putchar('\n');
		for (auto arr : res) {
			write(arr.size()); 
			for (int i : arr) putchar(' '), write(i);
			putchar('\n');
		}
	}
	return 0;
}


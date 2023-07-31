#include<bits/stdc++.h>
using namespace std;
using ll = long long;
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
const int N = 3e5 + 5;
int a[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	indexed_set st;
	int res = 0;
	for (int i = 0; i < n; ++i) {
		int cur = st.get(a[i] - 1) + 1;
		res = max(res, cur);
		st.update(a[i], cur);
	}
	cout << res;
	return 0;
}


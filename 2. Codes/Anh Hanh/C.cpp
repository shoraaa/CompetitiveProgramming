#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "geometry";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		ll res = 0;
		for (int i = 0, x, y; i < n; ++i) {
			cin >> x >> y;
			res += ll(x) * y;
		}
		cout << res << '\n';
	}
	return 0;
}


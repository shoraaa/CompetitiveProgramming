#include<bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0);
	n = 10, m = 10;
	cout << n << ' ' << m << '\n';
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cout << rng() % 10 + 1 << ' ';
		}
		cout << '\n';
	}
	return 0;
}

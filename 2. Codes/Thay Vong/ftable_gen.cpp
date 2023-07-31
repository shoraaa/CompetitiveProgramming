#include<bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 3, M = 5;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	int n = rng() % N + 1, m = rng() % N + 1;
	cout << n << ' ' << m << '\n';
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int v = rng() % M;
			if (rng() & 1) v = -v;
			cout << v << ' ';
		}
		cout << '\n';
	}
	return 0;
}


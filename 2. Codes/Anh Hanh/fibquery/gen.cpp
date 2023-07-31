#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 5;
const ll L = 10;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	int n = rng() % N + 1, q = rng() % N + 1;
	cout << n << ' ' << q << '\n';
	while (q--) {
		int t = rng() % 2 + 1, r = rng() % n + 1, l = rng() % r + 1;
		cout << t << ' ' << l << ' ' << r << ' ';
		if (t == 1) cout << rng() % L << '\n';
		else cout << '\n';
	}
	return 0;
}


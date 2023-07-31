#include<bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 50;
ll s[N], p[N];

int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	int n = rng() % N + 1, m = rng() % N + 1, q = rng() % N + 1;
	cout << n << ' ' << m << ' ' << q << '\n';
	for (int i = 1; i <= n; ++i) s[i] = rng() % N + 1;
	for (int i = 0; i <= n; ++i) p[i] = rng() % N + n + 1;
	sort(s + 1, s + n + 1);
	sort(p, p + n + 1, greater<ll>());
	for (int i = 1; i <= n; ++i) s[i] += i, cout << s[i] << " \n"[i == n];
	for (int i = 0; i <= n; ++i) p[i] -= i, cout << p[i] << " \n"[i == n];
	for (int i = 0; i < m; ++i) {
		int r = rng() % N + 1, l = rng() % r + 1;
		cout << l << ' ' << r << '\n';
	}
	for (int i = 0; i < q; ++i) {
		int t = rng() % N + 1;
		cout << t << '\n';
	}
	return 0;
}


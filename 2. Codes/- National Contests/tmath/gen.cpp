#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e2, M = 1e3;
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	int n = rng() % N + 1, t = rng() % M + 1;
	cout << n << ' ' << t << '\n';
	for (int i = 0; i < n; ++i)
		cout << rng() % M + 1 << ' ';
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 30, M = 1e9 + 1;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cout << N << ' ' << (N*(N+1)/2) << '\n';
	for (int i = 0; i < N; ++i)
		cout << rng() % M << ' ';
	return 0;
}


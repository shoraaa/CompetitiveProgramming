#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "divseq";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int M = 1e9 + 19972207;
ll pw(ll x, ll k) {
	ll res = 1;
	for (; k; k >>= 1, x = x * x % M) 
		if (k & 1) res = res * x % M;
	return res;
}
ll C(ll n, ll k) {
	ll a = 1, b = 1;
	for (ll i = n-k+1; i <= n; ++i)
		a = (i % M * a) % M;
	for (ll i = 1; i <= k; ++i)
		b = (i % M * b) % M;
	return a * pw(b, M - 2) % M;
}
ll n, k;
int32_t main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n >> k;
	ll res = 1;
	int c = 0;
	for (ll p = 2; p * p <= n; ++p) if (n % p == 0) {
		c = 0;
		while (n % p == 0) n /= p, c++;
		res = res * C(c + k - 1, c) % M;
	}
	if (n > 1) res = k % M * res % M;
	cout << res;
	return 0;
}


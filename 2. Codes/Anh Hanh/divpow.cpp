#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
void file() {
	const string FILE_NAME = "divpow";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int c(int n, int d) {
	int res = 2;
	for (int i = 2; i * i <= n; ++i) {
		if (i * i == n) res++;
		else if (n % i == 0) res += 2;
		if (res > d) return 0; 
	}
	return res == d;
}
ll pw(ll x, ll k) {
	ll res = 1;
	for (; k; k >>= 1, x *= x) if (k & 1)
		res *= x;
	return res;
}
int f(ll& n, ll k, ll r) {
	for (int i = -1; i <= 1; ++i) {
		if (pw(n + i, k) == r) return n += i, 1;
	}
	return 0;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	ll k;
	cin >> k;
	ll res = -1;
	for (int i = 2; i <= 62; ++i) {
		ll n = floor(pow(k, 1.0 / i));
		if (!f(n, i, k)) continue;
		if (!c(n, i)) continue;
		if (res == -1) res = n;
		else res = min(res, n);
	}	
	cout << res;
	return 0;
}


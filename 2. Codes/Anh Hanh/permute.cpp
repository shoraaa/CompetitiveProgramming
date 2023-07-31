#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "permute";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 4e5 + 5, M = 998244353;
void add(int& x, int y) {
	x += y; if (x >= M) x -= M;
}
void sub(int& x, int y) {
	x -= y; if (x < 0) x += M;
}
int dif(int x, int y) {
	x -= y; if (x < 0) x += M; return x;
}
ll fac[N], inv[N];
ll pw(ll x, ll k) {
	ll res = 1;
	for (; k; k >>= 1, x = x * x % M)
		if (k & 1) res = res * x % M;
	return res;
}
ll C(int n, int k) {
	if (n < k) return 0LL;
	return fac[n] * inv[k] % M * inv[n-k] % M;
}
int a[N], locked[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
	cin >> n >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		if (a[i] != -1) locked[a[i]] = 1;
	}
	int lockable = 0, permutable = 0;
	for (int i = 1; i <= n; ++i) if (a[i] == -1) {
		if (!locked[i]) lockable++;
		permutable++;
	}
	fac[0] = inv[0] = 1;
	for (int i = 1; i <= n; ++i)
		fac[i] = fac[i-1] * i % M, inv[i] = pw(fac[i], M-2);
	int res = 0;
	cerr << lockable << ' ' << permutable << '\n';
	for (int k = 1; k <= lockable; ++k) {
		// C(n, k) * fac[n-k]
		int cur = C(lockable, k) * fac[permutable-k] % M;
		cerr << cur << " \n"[k == lockable];
		if (k & 1) add(res, cur);
		else sub(res, cur);
	}
	cout << dif(fac[permutable], res);
	return 0;
}


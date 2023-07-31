#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5, M = 1e9 + 7;
void add(int& x, int y) {
	x += y; if (x >= M) x -= M;
}
void sub(int& x, int y) {
	x -= y; if (x < 0) x += M;
}
int dif(int x, int y) {
	x -= y; if (x < 0) x += M; return x;
}
int mul(ll x, ll y) {
	return x * y % M;
}
int pw(ll x, ll k) {
	ll res = 1;
	for (; k; k >>= 1, x = mul(x, x)) 
		if (k & 1) res = mul(res, x);
	return res;
}
int a[N], per[N];
int C(int n, int k) {
	if (n < k) return 0;
	return ll(per[n]) * pw(per[k], M - 2) % M * pw(per[n-k], M - 2) % M;
}
int n, m, k = 0;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0, l, r; i < m; ++i)
		cin >> l >> r, 
		a[l]++, a[r+1]--;
	for (int i = 1; i <= n; ++i)
		a[i] += a[i-1], k += a[i] > 0;
	per[0] = 1;
	for (int i = 1; i <= n; ++i)
		per[i] = mul(per[i-1], i);
	int inv = 0;
	for (int i = 1; i <= k; ++i) {
		int cur = mul(C(k, i), per[n-i]);
		if (i & 1) add(inv, cur);
		else sub(inv, cur);
	} 
	cout << dif(per[n], inv);
	return 0;
}


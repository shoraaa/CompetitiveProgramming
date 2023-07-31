#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int K = 20, N = (1 << K) + 6;
const int M = 1e9 + 7; 
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
int per[N];
int C(int n, int k) {
	if (n < k) return 0;
	return ll(per[n]) * pw(per[k], M - 2) % M * pw(per[n-k], M - 2) % M;
}
int siz[N], f[N];
int n, k, L, R;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> k >> L >> R;
	for (int i = 0, x; i < n; ++i)
		cin >> x, siz[x]++;
		
	for (int i = 0; i < K; ++i)
		for (int msk = 0; msk < 1 << K; ++msk) 
			if (msk >> i & 1) siz[msk] += siz[msk ^ (1 << i)];

	per[0] = 1;
	for (int i = 1; i <= n; ++i)
		per[i] = mul(per[i-1], i);
	
	for (int msk = 0; msk < 1 << K; ++msk)
		f[msk] = C(siz[msk], k);

	for (int i = 0; i < K; ++i)
		for (int msk = 0; msk < 1 << K; ++msk) if (msk >> i & 1) 
		 	sub(f[msk], f[msk ^ (1 << i)]);
		
	int res = 0;
	for (int i = L; i <= R; ++i) 
		if (i % 3 == 0) add(res, f[i]);
	cout << res;
	return 0;
}
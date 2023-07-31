#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "binary";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	ll n, k;
	cin >> n >> k;
	ll x = 0; int i = 0;
	for (i = 0; i < k || x < n; ++i)
		x = x * 2 + 1;
	i--; 
	int len = 0, mlen = 0;
	for (; i >= k; --i) if (x >> i & 1)
		if (x - (1LL << i) >= n) x ^= 1LL << i, mlen = max(mlen, len), len = 0;
		else len++;
	mlen = max(mlen, len);
	if (mlen >= k) {
		for (; ~i; --i) if (x >> i & 1) 
			if (x - (1LL << i) >= n) x ^= 1LL << i;
	} else { 
		for (i -= k - len; i >= 0; --i) if (x >> i & 1) 
			if (x - (1LL << i) >= n) x ^= 1LL << i;
	}
	cout << x;
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "flowers";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int M;
const int N = 1e6;
ll g[N + 5], inv[N + 5];
ll pw(ll x, ll k) {
	ll res = 1;
	for (; k; k >>= 1, x = (x * x) % M) if (k & 1)
		res = (res * x) % M;
	return res;
}
bool p[N + 5];
vector<int> get(vector<int>& pr, int n) {
	vector<int> a(pr.size());
	for (int i = 0; i < pr.size(); ++i) {
		ll cur = pr[i], base = pr[i];
		while (cur <= n) 
			a[i] += n / cur,
			cur *= base;
	}
	return a;
}
ll C(int n, int k) {
	if (n < k) return 0;
	if (M == 220797) {
		vector<int> pr;
		for (int i = 2; i <= n; ++i) if (!p[i]) 
			pr.emplace_back(i);
		vector<int> a = get(pr, n), b = get(pr, k), c = get(pr, n-k);
		for (int i = 0; i < pr.size(); ++i)
			a[i] -= b[i] + c[i];
		ll res = 1;
		for (int i = 0; i < pr.size(); ++i)
			res = (res * pw(pr[i], a[i])) % M;
		return res;
	}
	if (n <= N && k <= N)
		return g[n] * pw(g[k], M-2) % M * pw(g[n-k], M-2) % M;
	ll res = 1;
		for (int i = 0; i < k; ++i)
			res = (res * (n - i)) % M;
		return res * pw(g[k], M-2) % M;
}
int n, m, k;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	int T;
	cin >> T >> M;
	g[0] = 1;
	for (int i = 1; i <= N; ++i) 	
		g[i] = (g[i-1] * i) % M;
		
	if (M == 220797) {
		p[0] = p[1] = 1;
		for (int i = 2; i * i <= N; ++i) 
			if (!p[i]) for (int j = i * i; j <= N; j += i) p[j] = 1;	
	}
		
	while (T--) {
		cin >> n >> m >> k;
		cout << C(n - 1, k) * pw(m - 1, k) % M * m % M << '\n'; 
	}
	return 0;
}


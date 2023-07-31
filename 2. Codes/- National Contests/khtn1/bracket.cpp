#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e6 + 5;
const ll oo = 1e18;
ll a[N], b[N], f[N];
int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m;
	ll sum_b = 0;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
		cin >> b[i], sum_b += b[i];
	for (int i = 0; i < n; ++i)
		f[i] = a[i] - b[i];
	sort(f, f + n);
	for (int i = 1; i < n; ++i)
		f[i] += f[i-1];
	// day tang ngoai tru -n
	vector<ll> cost(4 * n);
	cost[-n + n] = 0;
	for (int i = -n + 2, c = 0 /* +1 */; i <= n; i += 2, c++) 
		cost[i + n] = f[c];
	// cost'[i] = min(cost[i], cost'[j] + cost'[i - j])
	ll res = oo;
	for (int i = -n; i <= n; i += 2)
		res = min(res, cost[i + n] * m / 2 + cost[-i + n] * m / 2);
	cout << sum_b * m + res + cost[0] * (m & 1);
	return 0;
}


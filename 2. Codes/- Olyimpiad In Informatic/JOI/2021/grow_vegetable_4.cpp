#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2e5 + 5;
ll a[N], pre[N], suf[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	a[0] = a[n+1] = -1e18;
	for (int i = 1; i <= n; ++i)
		pre[i] = pre[i-1] + max(0LL, a[i-1] + 1 - a[i]);
	for (int i = n; i; --i)
		suf[i] = suf[i+1] + max(0LL, a[i+1] + 1 - a[i]);
	ll res = 2e18;
	for (int i = 1; i <= n; ++i)
		res = min(res, max(pre[i], suf[i]));
	cout << res;
	return 0;
}


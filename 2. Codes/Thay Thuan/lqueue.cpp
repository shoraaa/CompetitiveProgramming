#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 5e5 + 5;
int a[N], f[N];
int n, x, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> x;
	for (int i = 1; i <= n; ++i)
		cin >> a[i], f[i] = f[i-1] + (a[i] >= x);
	cin >> q;
	for (int t, i, b = 0; q--;) {
		cin >> t;
		if (t == 1) n++, cin >> a[n], f[n] = f[n-1] + (a[n] >= x);
		else if (t == 2) b++;
		else cin >> i, cout << f[i+b] - f[b] << '\n';
	}
	return 0;
}


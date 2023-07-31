#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
int n, x;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> x;
	if (x == 1 || x == n * 2 - 1)
		return cout << "No", 0;
	vector<int> a(n * 2), pos(n * 2);
	for (int i = 1; i <= n * 2 - 1; ++i)
		a[i] = i, pos[i] = i;
	if (n == 2) {
		cout << "Yes\n";
		for (int i = 1; i <= n * 2 - 1; ++i)
			cout << a[i] << ' ';
		return 0;
	}
	auto sw = [&](int x, int y) {
		pos[a[y]] = pos[x];
		swap(a[pos[x]], a[y]);
		pos[x] = y;
	};
	if (x == 2) {
		sw(x, n);
		sw(x+1, n-1);
		sw(x-1, n+1);
		sw(x+2, n+2);
	} else {
		sw(x, n);
		sw(x-1, n-1);
		sw(x+1, n+1);
		sw(x-2, n+2);
	}
	cout << "Yes\n";
	for (int i = 1; i <= n * 2 - 1; ++i)
		cout << a[i] << ' ';
	return 0;
}


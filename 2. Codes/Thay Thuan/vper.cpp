#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5 + 5;
int a[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	sort(a, a + n);
	vector<int> c;
	int base = 0;
	for (int i = 0; i < n;) {
		int j = i;
		c.emplace_back(a[i]);
		while (j < n && a[j] == a[i]) j++; 
		base += j - i - 1, i = j;
	}
	int res = 1e9; n = c.size();
	for (int i = 0; i < n; ++i)
		res = min(res, c[i] - (i + 1) + (n - i - 1));
	cout << res + base;
	return 0;
}


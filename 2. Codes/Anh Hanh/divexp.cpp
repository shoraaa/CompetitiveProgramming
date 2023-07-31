#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "divexp";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e7 + 5;
int f[N];
int c(int r) {
	int i = 1, res = 0;
	for (int i = 1; i <= r;) {
		int x = r/i, j = r / x;
		res += x * (j - i + 1);
		i = j + 1;
	}
	return res; 
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	int l, r, d;
	cin >> l >> r >> d;
	for (int i = 1;; ++i) {
		int dk = 1;
		for (int j = 0; j < d; ++j) dk *= i;
		if (dk > r) break;
		for (int j = dk; j <= r; j += dk) f[j]++;
	}
	for (int i = 2; i <= r; ++i)
		f[i] += f[i-1];
	cout << c(r) - c(l-1) - (f[r] - f[l-1]);
	return 0;
}


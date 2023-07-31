#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e7 + 5, M = 1e9 + 7;
int f[N][3];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	f[1][0] = 1;
	f[2][2] = 2;
	for (int i = 3; i <= n; ++i)
		f[i][0] = f[i-1][0] * (i-2) + f[i-1][1],
		f[i][1] = f[i-1][1] * (i-3) + f[i-1][2] * (i-2),
		f[i][2] = f[i-1][0] * 2 + f[i-1][2],
		printf("%d : %d %d %d\n", i, f[i][0], f[i][1], f[i][2]);
	cout << f[n][0] << '\n';
	return 0;
}


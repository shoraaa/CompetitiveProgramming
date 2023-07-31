#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3000 + 5;
char s[N][N];
int n, m;
int get(int i, int j) {
	return (1 << 0) * (s[i][j] == 'G' && s[i][j-1] == 'R' && s[i][j+1] == 'W')
			 + (1 << 1) * (s[i][j] == 'G' && s[i-1][j] == 'R' && s[i+1][j] == 'W');
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> s[i][j];
	int res = 0;
	for (int d = 1; d <= n + m - 1; ++d) {
		int i = min(n, d), j = max(1, d - n + 1);
		int V = 0, H = 0, t1 = 0, t2 = 0;
		while (i >= 1 && j <= m) {
			t1 = max(V, H);
			int v = get(i, j);
			if (v & (1 << 0)) H = max(H, t2) + 1;
			if (v & (1 << 1)) V = max(V, t2) + 1; 
			t2 = t1;
			i--, j++;
		}
		res += max(H, V);
	}
	cout << res;
	return 0;
}


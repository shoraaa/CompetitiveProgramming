#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1000 + 5;
int a[N][N];
int n, m, q;
#define TOP_RIGHT 0
#define BOTTOM_LEFT 1
int rec(int i, int j, int oi, int oj) {
	if (i >= n || j >= m || (i <= oi && j >= oj)) return 0;
	if (on_path[i][j][TOP_RIGHT]) return 1;
	if (rec(i, j+1, oi, oj) || rec(i+1, j, oi, oj)) 
		return on_path[i][j][TOP_RIGHT] = 1;
	return 0;
}
void fix_tr_path(int x, int y) {
	// tim hang ma minh se di tiep
	int oi = i, oj = j;
	while (i != 0 || on_path[i-1][j][TOP_RIGHT]) i--;
	j--; 
	rec(i, j, oi, oj);
	for (int ni = np.first, nj = np.second; ni != i && nj != j;) {
		while (ni != 0 || on_path[ni-1][nj][TOP_RIGHT]) ni--;
		while (nj != 0 || on_path[ni][nj-1][TOP_RIGHT]) nj--;
	}
	
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		on_path[i][0][BOTTOM_LEFT] = on_path[i][n-1][TOP_RIGHT] = 1;
	for (int j = 0; j < m; ++j)
		on_path[0][j][TOP_RIGHT] = on_path[n-1][j][BOTTOM_LEFT] = 1;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		cin >> a[i][j];
		if (a[i][j])
			fix_path(i, j, TOP_RIGHT),
			fix_path(i, j, BOTTOM_LEFT);
	}
	cin >> q;
	for (int i, j; q--; ) {
		cin >> i >> j, i--, j--;
		if (on_path[i][j][TOP_RIGHT] && on_path[i][j][BOTTOM_LEFT])
			cout << 0 << '\n';
		else 
			cout << 1 << '\n',
			fix_path(i, j, TOP_RIGHT),
			fix_path(i, j, BOTTOM_LEFT);
	}
	return 0;
}


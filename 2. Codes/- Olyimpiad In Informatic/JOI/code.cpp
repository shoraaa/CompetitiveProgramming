#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3000 + 5;
string s[N];
int n, m, d = 0;
int pos[N][N][2]; // left down right up
#define LEFT 0
#define DOWN 1
int tag(int i, int j, int dir) {
	if (i < 0 || j < 0 || i >= n || j >= m) return 0;
	return pos[i][j][dir];
}
vector<int> G[N * N / 3];
int c[2];
bitset<N * N / 3> vis;
void call(int u, int e = 0) {
	vis[u] = 1, c[e]++;
	for (int v : G[u]) if (!vis[v])
		call(v, e ^ 1);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> s[i];
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		if (j <= m-3 && s[i][j] == 'R' && s[i][j+1] == 'G' && s[i][j+2] == 'W') pos[i][j][LEFT] = ++d;
		if (i <= n-3 && s[i][j] == 'R' && s[i+1][j] == 'G' && s[i+2][j] == 'W') pos[i][j][DOWN] = ++d;
		//if (pos[i][j][LEFT]) printf("%d %d LEFT = %d\n", i+1, j+1, pos[i][j][LEFT]);
		//if (pos[i][j][DOWN]) printf("%d %d DOWN = %d\n", i+1, j+1, pos[i][j][DOWN]);
	}
	for (int i = 0, u, v; i < n; ++i) for (int j = 0; j < m; ++j) {
		if (u = pos[i][j][LEFT]) {
			if (v = pos[i][j][DOWN]) G[u].emplace_back(v);
			
			if (v = tag(i-1, j+1, DOWN)) G[u].emplace_back(v);
			if (v = tag(i-2, j+2, DOWN)) G[u].emplace_back(v);
		}
		if (u = pos[i][j][DOWN]) {
			if (v = pos[i][j][LEFT]) G[u].emplace_back(v);
			
			if (v = tag(i+1, j-1, LEFT)) G[u].emplace_back(v);
			if (v = tag(i+2, j-2, LEFT)) G[u].emplace_back(v);
		}
	}
	int res = 0;
	for (int i = 1; i <= d; ++i) if (!vis[i]) {
		c[0] = 0, c[1] = 0, call(i);
		res += max(c[0], c[1]);
	}
	cout << res;
	return 0;
}


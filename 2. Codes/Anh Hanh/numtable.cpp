#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "numtable";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 4e4;
vector<vector<int>> a, vis;
int lp[N + 5];
vector<int> pr;
int n, m, cur_p;
int dfs(int i, int j) {
	if (i < 0 || j < 0 || i >= n || j >= m || vis[i][j] || a[i][j] % cur_p != 0) return 0;
	return vis[i][j] = 1, dfs(i - 1, j) + dfs(i + 1, j) + dfs(i, j - 1) + dfs(i, j + 1) + 1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
	int t;
	cin >> t;
	
	cin >> n >> m;
	a.resize(n, vector<int>(m)), vis = a;
	int M = 0;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
		cin >> a[i][j], M = max(M, a[i][j]);
	
	for (int i = 2; i <= N; ++i) {
		if (lp[i] == 0)
			lp[i] = i,
			pr.emplace_back(i);
		for (int p : pr) {
			if (p > lp[i] || p * i > N) break;
			lp[p * i] = p;
		}
	}
	cerr << pr.size() << '\n';
	int res = 1;
	for (int p : pr) {
		vis = vector<vector<int>>(n, vector<int>(m));
		cur_p = p;
		for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) 
			if (!vis[i][j]) res = max(res, dfs(i, j));
	}
	vis = vector<vector<int>>(n, vector<int>(m));
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
		if (!vis[i][j]) cur_p = a[i][j], res = max(res, dfs(i, j));
	cout << res;
	return 0;
}


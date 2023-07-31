#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "nazi";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e2 + 5;
int vis[N][N];
int n, m, k;
struct S {
	int x, y, t;
	S(int x, int y, int t): x(x), y(y), t(t) {}
};
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n >> m >> k;
	queue<S> q;
	for (int i = 0, x, y; i < k; ++i) 
		cin >> x >> y, x--, y--,
		q.emplace(x, y, 1);
	int res = 1;
	while (!q.empty()) {
		auto s = q.front(); q.pop();
		int x = s.x, y = s.y, t = s.t;
		if (x < 0 || y < 0 || x >= n || y >= m || vis[x][y]) continue;
		vis[x][y] = 1; res = max(res, t);
		q.emplace(x + 1, y, t + 1);
		q.emplace(x, y + 1, t + 1);
		q.emplace(x - 1, y, t + 1);
		q.emplace(x, y - 1, t + 1);
	}
	cout << res;
	return 0;
}


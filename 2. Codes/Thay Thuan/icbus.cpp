#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5000 + 5;
int a[N], b[N], dis[N][N];
vector<int> G[N];
int n, m;
struct S {
	int u, i, d;
	S(int u, int i, int d): u(u), i(i), d(d) {}
	bool operator < (const S& s) const {
		return d > s.d;
	}
};
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> a[i] >> b[i];
	for (int i = 0, u, v; i < m; ++i)
		cin >> u >> v, u--, v--,
		G[u].emplace_back(v),
		G[v].emplace_back(u);
	// dis[u][i] la chi phi nho nhat den u va chi dc di i buoc nua
	memset(dis, 0x3f, sizeof(dis));
	priority_queue<S> q;
	q.emplace(0, b[0], a[0]);
	dis[0][b[0]] = a[0];
	int res = 1e9;
	while (!q.empty()) {
		S s = q.top(); q.pop();
		if (s.d != dis[s.u][s.i]) continue;
		if (s.u == n-1)
			res = min(res, s.d);
		for (int v : G[s.u]) {
			// di tiep <> i > 0
			if (s.i > 0 && s.d < dis[v][s.i-1])
				dis[v][s.i-1] = s.d, q.emplace(v, s.i-1, s.d);
			// di tiep tu u
			if (s.d + a[s.u] < dis[v][b[s.u] - 1]) 
				dis[v][b[s.u] - 1] = s.d + a[s.u], q.emplace(v, b[s.u] - 1, s.d + a[s.u]);
		}
	}
	cout << res;
	return 0;
}


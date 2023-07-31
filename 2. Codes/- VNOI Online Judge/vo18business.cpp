#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 5;
vector<int> G[N];
int n, k, d;
queue<int> q;
int dep[N], dis[N];
int farthest(int u, int e = -1) {
	if (e == -1) dep[u] = 0;
	else dep[u] = dep[e] + 1;
	int res = dis[u] > d ? u : -1;
	for (int v : G[u]) if (v != e) {
		int rv = farthest(v, u);
		if (res == -1) res = rv;
		else if (rv != -1) res = dep[rv] > dep[res] ? rv : res; 
	}
	return res;
} 
int check() {
	int r = 0;
	while (r < n && dis[r] <= d) r++;
	if (r == n) return 1;
	int u = farthest(r); 
	int	v = farthest(u);
	return d >= (dep[v] + 1) / 2;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> k;
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 0, u; i < k; ++i)
		cin >> u, u--,
		dis[u] = 0, q.emplace(u);
	for (int i = 0, u, v; i < n-1; ++i)
		cin >> u >> v, u--, v--,
		G[u].emplace_back(v),
		G[v].emplace_back(u);
	while (!q.empty()) {
		auto u = q.front(); q.pop();
		for (int v : G[u]) if (dis[u] + 1 < dis[v])
			dis[v] = dis[u] + 1, q.emplace(v);
	}
	int lo = 0, hi = n-1, mid, ans = n-1;
	while (lo <= hi) {
		d = mid = (lo + hi) >> 1;
		if (check())
			ans = mid,
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	cout << ans;
	return 0;
}


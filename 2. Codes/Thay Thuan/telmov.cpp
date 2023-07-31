#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
struct C {
	int v, w;
	C(int v, int w): v(v), w(w) {}
};
struct S {
	int u, d;
	S(int u, int d): u(u), d(d) {}
	bool operator < (const S& s) const {
		return d > s.d;
	}
};
vector<C> G[N];
int dis[N][11][11];
bitset<N> vis;
int n, m, p, l, k;
void add_edge(int u) {
	vis[u] = 1;
	for (C& c : G[u]) if (dis[u] + c.w == dis[c.v]) {
		T[c.v].emplace_back(u, c.w);
		if (!vis[c.v]) add_edge(c.v);
	}
}
int call(int u, int t) {
	if (u == 0)
		return 0;
	if (dp[u][t]) 
		return dp[u][t];
	int res = 2e9;
	queue<S> qu;
	for (C& c : T[u])
		res = min(res, call(c.v, t) + c.w),
		qu.emplace(c.v, c.w, 1);
	while (!qu.empty()) {
		S s = qu.front(); qu.pop();
		if (s.dep > l) continue;
		res = min(res, call(s.u, t - 1) + p);
		if (s.dep == l) continue;	
		for (C& c : T[s.u]) 
			qu.emplace(c.v, s.d + c.w, s.dep + 1);
	}
	return dp[u][t] = res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m >> p >> l >> k;
	for (int i = 0, u, v, w; i < m; ++i)
		cin >> u >> v >> w, u--, v--,
		G[u].emplace_back(v, w),
		G[v].emplace_back(u, w);
	memset(dis, -1, sizeof(dis));
	dis[0] = 0;
	priority_queue<S> q;
	q.emplace(0, 0);
	while (!q.empty()) {
		S s = q.top(); q.pop();
		if (s.d != dis[s.u]) continue;
		dp[s.u][0] = s.d;
		
		for (C& c : G[s.u]) if (dis[c.v] == -1 || s.d + c.w < dis[c.v])
			dis[c.v] = s.d + c.w, q.emplace(c.v, s.d + c.w);
	}
	cout << res;
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5, M = 7e5 + 5, MOD = 998244353;
int mul(ll x, ll y) {
	return x * y % MOD;
}
int dif(int x, int y) {
	x -= y; if (x < 0) x += MOD; return x;
}
int pw(ll x, ll k) {
	ll res = 1;
	for (; k; k >>= 1, x = mul(x, x)) 
		if (k & 1) res = mul(res, x);
	return res;
}
struct C {
	int v, i;
	C(int v, int i): v(v), i(i) {}
};
struct S {
	int u;
	ll d;
	S(int u, ll d): u(u), d(d) {}
	bool operator < (const S& s) const {
		return d > s.d;
	}
};
vector<C> G[N], T[N];
int e[M], cnt[N]; 
ll dis[N];
bool vis[N], ck[N];
int n, m, k;
vector<int> ord;
void topo(int u) {
	vis[u] = 1;
	for (C& c : T[u]) 
		topo(c.v);
	ord.emplace_back(u);
}
void dfs(int u) {
	vis[u] = 1;
	for (C& c : T[u]) 
		dfs(c.v);
}

int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> m >> k;
	for (int i = 0, u, v, w; i < m; ++i)
		cin >> u >> v >> w, u--, v--,
		G[u].emplace_back(v, i),
		G[v].emplace_back(u, i),
		e[i] = w;
	for (int i = m, v, w; i < m + k; ++i)
		cin >> v >> w, v--,
		G[0].emplace_back(v, i),
		G[v].emplace_back(0, i),
		e[i] = w;
		
	priority_queue<S> q;
	q.emplace(0, 0);
	memset(dis, 0x3f, sizeof(dis));
	dis[0] = 0;
	while (!q.empty()) {
		S s = q.top(); q.pop();
		if (s.d != dis[s.u]) continue;
		for (C& c : G[s.u]) if (s.d + e[c.i] < dis[c.v])
			dis[c.v] = s.d + e[c.i],
			q.emplace(c.v, dis[c.v]);
	}
	for (int u = 0; u < n; ++u) for (C& c : G[u]) 
		if (dis[u] + e[c.i] == dis[c.v]) T[u].emplace_back(c.v, c.i);
		
	for (int u = 1; u < n; ++u) 
		if (!vis[u]) topo(u);
	reverse(ord.begin(), ord.end());
	
	memset(vis, 0, sizeof(vis));
	for (C& c : T[0]) {
		if (c.i < m && !vis[c.v]) dfs(c.v);
		if (c.i >= m) cnt[c.v]++;
	}
	
	for (int u : ord) if (!vis[u]) 
		ck[u] = 1, k -= cnt[u], dfs(u);

	ll res = pw(2, k);
	for (int u : ord) if (ck[u]) 
		res = mul(res, dif(pw(2, cnt[u]), 1));
	cout << res;
	
	return 0;
}
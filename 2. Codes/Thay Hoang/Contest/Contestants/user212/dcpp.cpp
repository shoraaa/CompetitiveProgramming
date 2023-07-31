#include <bits/stdc++.h>
#define FNAME "DCPP"
using namespace std;

#define BIT(x, i) ((x) >> (i) & 1)

typedef pair<int, int> pii;
#define fi first
#define se second

const int N = 1e3 + 5, oo = 2e9 + 123;

struct Item {
	int u, d;
	bool operator < (const Item &x) const {
		return d > x.d;
	}
};

int n, m, s, t, rem[N][N], deg[N], p[N], d[N], w[N][N];
vector<int> g[N];

void build_graph() {
	vector<int> mor, les;
	for (int i = 1; i <= n; ++i)
		if (deg[i] > 0) 
			mor.emplace_back(i);

		else if (deg[i] < 0)
			les.emplace_back(i);
	s = n + 1, t = n + 2; n += 2;
	for (int &v : mor) 
		g[s].emplace_back(v),
		g[v].emplace_back(s),
		rem[s][v] = oo;
	for (int &v : les)
		g[v].emplace_back(t),
		g[t].emplace_back(v),
		rem[v][t] = oo;
}

bool dijkstra(vector<int> &par) {
	priority_queue<Item> Q;
	for (int i = 1; i <= n; ++i)
		par[i] = -1, d[i] = oo;
	d[s] = 0;
	Q.push({s, 0});
	while (Q.size()) {
		Item cur = Q.top(); Q.pop();
		if (d[cur.u] != cur.d) continue;
		for (int &v : g[cur.u]) {
			int _d = cur.d + w[cur.u][v] + p[cur.u] - p[v];
			if (rem[cur.u][v] == 0) continue;
			if (d[v] > _d) {
				d[v] = _d;
				Q.push({v, _d});
				par[v] = cur.u;
			}
		}
	}
	for (int i = 1; i <= n; ++i) 
		p[i] += d[i];// cout << d[i] << " \n"[i == n];
	return d[n] != oo;
}

int min_cost() {
	int ans = 0;
	vector<int> par(n + 1);
	while (dijkstra(par)) {
		int inc = oo, v = t;
		while (v != s) 
			inc = min(inc, rem[par[v]][v]),
			v = par[v],
			ans += w[par[v]][v];
		v = t;
		while (v != s) {
			int u = par[v];
			rem[u][v] -= inc;
			rem[v][u] += inc;	
			v = u;
		}
	}	
	return ans;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
	if (fopen(FNAME".inp", "r")) {
		freopen(FNAME".inp", "r", stdin);
		freopen(FNAME".out", "w", stdout);
	}
	cin >> n >> m;
	int res = 0;
	for (int u, v, c; m > 0; --m) {
		cin >> u >> v >> c;
		--deg[u]; ++deg[v];
		res += c;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
		rem[u][v] = oo;
		w[u][v] = c;
		w[v][u] = -c;
	}
	build_graph();
	res += min_cost();
	cout << res;
	return 0;
}
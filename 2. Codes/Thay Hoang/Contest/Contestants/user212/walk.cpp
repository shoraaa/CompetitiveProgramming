#include <bits/stdc++.h>
#define FNAME "WALK"
using namespace std;
using ll = long long;

#define BIT(x, i) ((x) >> (i) & 1)

typedef pair<int, int> pii;
#define fi first
#define se second

const int N = 1e5 + 5;
const ll oo = 1e17;

int n, m, num_e = 0;
ll p[N], d[N];

struct Edge {
	int u, v, w, rem;
	Edge() {}
	Edge(int u, int v, int w, int rem)
		: u(u), v(v), w(w), rem(rem) {} 
	inline int adj(int x) {
		return (x == u ? v : u);
	}
} E[4 * N];

struct Item {
	int u;
	ll d;
	inline bool operator < (const Item &x) const {
		return d > x.d;
	}
};

vector<int> g[N];

inline ll wei(int i) {
	// cout << p[E[i].u] << ' ' << p[E[i].v] << '\n';
	return E[i].w + p[E[i].u] - p[E[i].v];
}

void dijkstra(vector<int> &par) {
	for (int i = 1; i <= n; ++i)
		par[i] = -1, d[i] = oo;
	priority_queue<Item> Q;
	d[1] = 0;
	Q.push({1, 0});
	// cout << "**\n";
	while (Q.size()) {
		auto cur = Q.top(); Q.pop();
		if (cur.d != d[cur.u]) continue;
		// cout << cur.u << ' ' << cur.d << ":\n";
		for (int &i : g[cur.u]) {
			if (E[i].rem == 0) continue; 
			int v = E[i].adj(cur.u);
			ll _d = wei(i) + cur.d;
			// cout << i << ' ' << E[i].w << ' ' << E[i].rem << ' ' << v << ' ' << _d << '\n';
			if (d[v] > _d) {
				d[v] = _d;
				Q.push({v, d[v]});
				par[v] = i;
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		p[i] += d[i];// cout << p[i] << " \n"[i == n];
}

void fix_aug(vector<int> &par) {
	int v = n;
	while (v != 1) {
		int i = par[v], u = E[i].adj(v);
		// cout << '*' << i << ' ' << (i ^ 1) << ' ' << E[i].u << ' ' << E[i].v << ' ' << E[i].w << '\n';
		--E[i].rem;
		++E[i ^ 1].rem;
		v = u;
	}
}

void trace(vector<int> &x, ll &s) {
	int u = 1;
	x.emplace_back(1);
	while (u != n) {
		for (int &i : g[u])
			if (E[i].w > 0 && E[i].rem == 0) {
				s += E[i].w;
				++E[i].rem;
				int v = E[i].adj(u);
				x.emplace_back(v);
				u = v;
				break;
			}
	}
}

void minCost() {
	vector<int> minPath[2];
	vector<int> par(n + 1);
	ll s = 0;
	for (int step = 0; step < 2; ++step) {
		vector<int> par(n + 1);
		dijkstra(par);
		if (d[n] == oo) {
			cout << -1;
			return;
		}
		fix_aug(par);
	}
	for (int i = 0; i < 2; ++i)
		trace(minPath[i], s);
	minPath[1].pop_back();
	reverse(minPath[1].begin(), minPath[1].end());
	cout << s << '\n';
	for (int &v : minPath[0]) cout << v << ' ';
	for (int &v : minPath[1]) cout << v << ' ';	
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
	if (fopen(FNAME".inp", "r")) {
		freopen(FNAME".inp", "r", stdin);
		freopen(FNAME".out", "w", stdout);
	}
	cin >> n >> m;
	for (int i = 1, u, v, w; i <= m; ++i) {
		cin >> u >> v >> w;
		E[num_e] = Edge(u, v, w, 1);
		g[u].emplace_back(num_e++);
		E[num_e] = Edge(v, u, -w, 0);
		g[v].emplace_back(num_e++);
		E[num_e] = Edge(v, u, w, 1);
		g[v].emplace_back(num_e++);
		E[num_e] = Edge(u, v, -w, 0);
		g[u].emplace_back(num_e++);
	}
	minCost();
	return 0;
}







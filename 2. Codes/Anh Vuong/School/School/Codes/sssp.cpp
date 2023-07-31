#include <bits/stdc++.h>
using namespace std;

template <class X, class Y>
bool cmin(X &a, const Y &b) {
	return a > b ? a = b, 1 : 0;
}

#define eb emplace_back

using ll = long long;

struct edge {
	int v; ll w;

	edge(int v, ll w): v(v), w(w) {}

	bool operator < (const edge &o) const {
		return w > o.w;
	}
};

const int N = 1e5 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;

vector <edge> adj[N * 9];
ll d[N * 9]; priority_queue <edge> pq;
int n, m, s, _l, _r, _u, _w;

int id(int i, int t) {
	if (t == 0) return i;
	if (t == 1) return i + n;
	return i + n * 5;
}

void init(int i, int l, int r) {
	if (l == r) {
		adj[id(i, 1)].eb(l, 0);
		adj[l].eb(id(i, 2), 0); return;
	}
	int m = (l + r) / 2;
	init(i * 2, l, m);
	init(i * 2 + 1, m + 1, r);
	adj[id(i, 1)].eb(id(i * 2, 1), 0);
	adj[id(i, 1)].eb(id(i * 2 + 1, 1), 0);
	adj[id(i * 2, 2)].eb(id(i, 2), 0);
	adj[id(i * 2 + 1, 2)].eb(id(i, 2), 0);
}

void up(int i, int l, int r) {
	if (l > _r || r < _l) return;
	if (l >= _l && r <= _r) {
		adj[_u].eb(id(i, 1), _w); return;
	}
	int m = (l + r) / 2;
	up(i * 2, l, m);
	up(i * 2 + 1, m + 1, r);
}

void down(int i, int l, int r) {
	if (l > _r || r < _l) return;
	if (l >= _l && r <= _r) {
		adj[id(i, 2)].eb(_u, _w); return;
	}
	int m = (l + r) / 2;
	down(i * 2, l, m);
	down(i * 2 + 1, m + 1, r);
}

void up(int u, int l, int r, int w) {
	_u = u; _l = l; _r = r; _w = w;
	up(1, 1, n);
}

void down(int u, int l, int r, int w) {
	_u = u; _l = l; _r = r; _w = w;
	down(1, 1, n);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m >> s; init(1, 1, n);
	for (int i = 1; i <= m; i++) {
		int t; cin >> t;
		if (t == 1) {
			int u, v, w;
			cin >> u >> v >> w;
			adj[u].eb(v, w);
		}
		if (t == 2) {
			int u, l, r, w;
			cin >> u >> l >> r >> w;
			up(u, l, r, w);
		}
		if (t == 3) {
			int u, l, r, w;
			cin >> u >> l >> r >> w;
			down(u, l, r, w);
		}
	}
	memset(d, 0x3f, sizeof d);
	pq.emplace(s, d[s] = 0);
	while (pq.size()) {
		edge cur = pq.top(); pq.pop();
		if (d[cur.v] < cur.w) continue;
		for (edge e : adj[cur.v])
			if (cmin(d[e.v], cur.w + e.w))
				pq.emplace(e.v, d[e.v]);
	}
	for (int i = 1; i <= n; i++)
		cout << (d[i] == inf ? -1 : d[i]) << ' ';
}
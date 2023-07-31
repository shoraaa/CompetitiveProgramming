#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll inf = 2e14;
int n, m;
vector<int> adj[100005];
ll p[100005], d[100005];
int trace[100005];
struct edge {
	int x, y, c, f;
	int w;
} e[400005];
vector<int> Path1, Path2;
ll w1=0, w2=0;

struct item {
	int v;
	ll dlab;
	inline bool Valid() const {
		return d[v] == dlab;
	}
	inline operator < (const item& other) const {
		return dlab > other.dlab;
	}
};

inline int cf(const edge& x) {
	return x.c - x.f;
}

inline ll wp(const edge& x) {
	return x.w + p[x.x] - p[x.y];
}

inline bool Minimize(ll& Target, ll Value) {
	if (Value < Target) {
		Target = Value;
		return true;
	}
	return false;
}

void Dijkstra() {
	fill(d + 1, d + n + 1, inf);
	d[1] = 0;
	priority_queue<item> PQ;
	PQ.push({1, 0});
	while (!PQ.empty()) {
		item c = PQ.top();
		PQ.pop();
		if (!c.Valid()) continue;
		int u = c.v;
		for (int i : adj[u]) {
			int v = e[i].y;
			if (cf(e[i]) == 0) continue;
			if (Minimize(d[v], d[u] + wp(e[i]))) {
				trace[v] = i;
				PQ.push({v, d[v]});
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		p[i] += d[i];
}

void AugmentFlow() {
	int u = n;
	while (u != 1) {
		int i = trace[u];
		e[i].f++;
		e[i ^ 1].f--;
		u = e[i].x;
	}
}

void FindPath(vector<int>&x, ll& weight) {
	int u = 1;
	x.push_back(1);
	while (true) {
		for (int i : adj[u])
			if (e[i].f == 1) {
				u = e[i].y;
				e[i].f = 0;
				weight += e[i].w;
				break;
			}
		x.push_back(u);
		if (u == n) break;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("WALK.INP", "r", stdin);
	freopen("WALK.OUT", "w", stdout);
	cin >> n >> m;
	int j = 0;
	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;
		e[j++] = {u, v, 1, 0, w};
		e[j++] = {v, u, 0, 0, -w};
		e[j++] = {v, u, 1, 0, w};
		e[j++] = {u, v, 0, 0, -w};
	}
	m = j;
	for (int i = 0; i < m; ++i)
		adj[e[i].x].push_back(i);
	fill(p + 1, p + n + 1, 0);
	for (int step = 0; step < 2; ++step) {
		Dijkstra();
		if (d[n] == inf) {
			cout << -1;
			return 0;
		}
		AugmentFlow();
	}
	FindPath(Path1, w1);
	FindPath(Path2, w2);
	Path1.pop_back();
	reverse(Path2.begin(), Path2.end());
	cout << w1 + w2 << "\n";
	for (int u : Path1) cout << u << " ";
	for (int u : Path2) cout << u << " ";
	return 0;
}

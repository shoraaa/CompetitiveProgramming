//source: 

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e3 + 10;

struct Edge {
	int from, to; ll capa, flow, cost;
	Edge (int _from, int _to, ll _capa, ll _cost) {
		from = _from; to = _to; capa = _capa; cost = _cost; flow = 0;
	}
};

vector<Edge> edges;
vector<int> adj[N];

void add_edge(int x, int y, ll capa, ll cost) {
	adj[x].push_back(edges.size());
	edges.push_back(Edge(x, y, capa, cost));
	adj[y].push_back(edges.size());
	edges.push_back(Edge(y, x, 0, -cost));
}

int source, sink;

ll d[N]; int at[N], pa[N], pe[N];
bool spfa() {
	memset(d, 127, sizeof(d)); memset(at, 0, sizeof(at));

	d[source] = 0; at[source] = 1;
	deque<int> q; q.push_back(source);

	while (q.size()) {
		int x = q.front(); q.pop_front();
		at[x] = 2;
		for (int i : adj[x]) {
			if (edges[i].flow < edges[i].capa) {
				int v = edges[i].to; ll w = edges[i].cost;
				if (d[v] > d[x] + w) {
					d[v] = d[x] + w;
					pa[v] = x; pe[v] = i;
					if (!at[v]) q.push_back(v);
					if (at[v] == 2) q.push_front(v);
					at[v] = 1;
				}
			}
		}
	}

	return at[sink] == 2;
}

pair<ll, ll> mcmf() {
	ll ret = 0, cost = 0;
	while (spfa()) {
		ll flow = 1e18;
		for (int v = sink; v != source; v = pa[v]) {
			int i = pe[v];
			flow = min(flow, edges[i].capa - edges[i].flow);
		}
		ret += flow;
		for (int v = sink; v != source; v = pa[v]) {
			int i = pe[v];
			edges[i].flow += flow; edges[i ^ 1].flow -= flow;
			cost += flow * edges[i].cost;
		}
	}
	return make_pair(ret, cost);
}

int in[N], out[N];

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	if (fopen("dcpp.inp", "r")) {
		freopen("dcpp.inp", "r", stdin);
		freopen("dcpp.out", "w", stdout);
	}
	
	int n, m; cin >> n >> m;
	source = 0, sink = m + 1;
	ll res = 0;
	for (int i = 1; i <= m; ++i) {
		int x, y,w ; cin >> x >> y >> w;
		++out[x]; ++in[y];
		add_edge(x, y, 1e9, w);
		res += w;
	}
	for (int x = 1; x <= n; ++x) if (in[x] > out[x]) add_edge(source, x, in[x] - out[x], 0);
	else if (in[x] < out[x]) add_edge(x, sink, out[x] - in[x], 0);

	cout << res + mcmf().second << "\n";
}
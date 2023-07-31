//source:

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 10;

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
		vector<int> cur_path;
		for (int v = sink; v != source; v = pa[v]) {
			int i = pe[v];
			edges[i].flow += flow; edges[i ^ 1].flow -= flow;
			cost += flow * edges[i].cost;
		}
	}
	return make_pair(ret, cost);
}

vector<tuple<int, int, int>> re[N];
bool dd[N];

void dijkstra(int s) {
	memset(d, 127, sizeof(d)); d[s] = 0;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
	q.push(make_pair(0, s));

	while (q.size()) {
		ll dist; int x; tie(dist, x) = q.top(); q.pop();
		if (dist != d[x]) continue;
		for (tuple<int, int, int> i : re[x]) {
			int v, idx; ll w; tie(v, w, idx) = i;
			if (d[v] > d[x] + w) {
				d[v] = d[x] + w;
				pa[v] = x; pe[v] = idx;
				q.push(make_pair(d[v], v));
			}
		}
	}
}

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	if (fopen("walk.inp", "r")) {
		freopen("walk.inp", "r", stdin);
		freopen("walk.out", "w", stdout);
	}

	int n, m; cin >> n >> m;
	source = 0, sink = n + 1;
	for (int i = 1; i <= m; ++i) {
		int x, y; ll w; cin >> x >> y >> w;
		add_edge(x, y, 1, w); add_edge(y, x, 1, w);
	}
	add_edge(source, 1, 2, 0); add_edge(n, sink, 2, 0);

	pair<ll, ll> mf = mcmf();
	if (mf.first != 2) return cout << -1, 0;
	cout << mf.second << "\n";

	for (int t = 0; t < edges.size(); ++t) {
		Edge i = edges[t];
		if (i.flow == 1) {
			re[i.from].push_back(make_tuple(i.to, i.cost, t));
			re[i.to].push_back(make_tuple(i.from, i.cost, t));
		}
	}

	for (int i = 1; i <= n; ++i) {
		//cout << re[i].size() << " ";
		assert(re[i].size() % 2 == 0);
	}
	//cout << "\n";

	dijkstra(1);
	vector<int> ans;
	for (int v = n; v != 1; v = pa[v]) {
		dd[pe[v]] = 1;
		ans.push_back(v);
		//cerr << v << " " << pe[v] << "\n";
	}
	reverse(ans.begin(), ans.end()); ans.pop_back();

	for (int v = n; v != 1; ) {
		bool ok = 1;
		for (tuple<int, int, int> i : re[v]) ok &= dd[get<2>(i)];
		assert(!ok);
		for (tuple<int, int, int> i : re[v]) if (!dd[get<2>(i)]) {
			ans.push_back(v);
			dd[get<2>(i)] = 1;
			v = get<0>(i);
			break;
		}
	}

	cout << "1 ";
	for (int i : ans) cout << i << " ";
	cout << "1\n";
}
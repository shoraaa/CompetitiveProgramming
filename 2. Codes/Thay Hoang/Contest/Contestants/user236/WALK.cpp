/*************************************
*    author: marvinthang             *
*    created: 18.07.2022 08:27:53    *
*************************************/

#include <bits/stdc++.h>

using namespace std;

#define                  fi  first
#define                  se  second
#define                 div  ___div
#define                left  ___left
#define               right  ___right
#define                TIME  (1.0 * clock() / CLOCKS_PER_SEC)
#define             MASK(i)  (1LL << (i))
#define             FULL(i)  (MASK(i) - 1)
#define           BIT(x, i)  ((x) >> (i) & 1)
#define  __builtin_popcount  __builtin_popcountll
#define        scan_op(...)  istream & operator >> (istream &in, __VA_ARGS__ &u)
#define       print_op(...)  ostream & operator << (ostream &out, const __VA_ARGS__ &u)
#define          file(name)  if (fopen (name".inp", "r")) { freopen (name".inp", "r", stdin); freopen (name".out", "w", stdout); }

template <class T>             scan_op(vector <T>)  { for (size_t i = 0; i < u.size(); ++i) in >> u[i]; return in; }
template <class T>            print_op(vector <T>)  { out << '{'; for (size_t i = 0; i + 1 < u.size(); ++i) out << u[i] << ", "; if (!u.empty()) out << u.back(); return out << '}'; }
template <class U, class V>   scan_op(pair <U, V>)  { return in >> u.fi >> u.se; }
template <class U, class V>  print_op(pair <U, V>)  { return out << '(' << u.fi << ", " << u.se << ')'; }

const double PI = 3.1415926535897932384626433832795; // acos(-1.0); atan(-1.0);
const int dir[] = {1, 0, -1, 0, 1, 1, -1, -1, 1};
const int MAX = 1e5 + 5;
const long long oo = 1e18;

struct Edge {
	int from, to;
	long long flow, cost, capa;
	Edge(int u = 0, int v = 0, long long ca = 0, long long co = 0):
		from(u), to(v), capa(ca), cost(co), flow(0) {};
	long long residual(void) const { return capa - flow; }
	bool saturating(void) { return !residual(); }
};

int N, M;
vector <vector <int>> adj;
vector <Edge> edges;
vector <long long> dist, trace;

int addEdge(int u, int v, long long ca, long long co) {
	adj[u].push_back(edges.size());
	edges.push_back(Edge(u, v, ca, co));
	adj[v].push_back(edges.size());
	edges.push_back(Edge(v, u, 0, -co));
	return edges.size() - 2;
}

bool FordBellman(int s, int t) {
	for (int i = 0; i < N + 5; ++i) {
		dist[i] = oo;
		trace[i] = -1;
	}
	vector <int> inQueue(N + 5, false);
	queue <int> q;
	dist[s] = 0; q.push(s), inQueue[s] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop(); inQueue[u] = false;
		for (int id: adj[u]) if (edges[id].residual() > 0) {
			int v = edges[id].to;
			if (dist[v] > dist[u] + edges[id].cost) {
				dist[v] = dist[u] + edges[id].cost;
				trace[v] = id;
				if (!inQueue[v]) {
					q.push(v);
					inQueue[v] = true;
				}
			}
		}
	}
	return dist[t] < oo;
}

pair <long long, long long> getFlow(int s, int t) {
	for (Edge &e: edges) e.flow = 0;
	long long totFlow = 0, totCost = 0;
	while (FordBellman(s, t)) {
		long long delta = oo;
		for (int u = t; u != s; u = edges[trace[u]].from) 
			delta = min(delta, edges[trace[u]].residual());
		for (int u = t; u != s; u = edges[trace[u]].from) {
			edges[trace[u]].flow += delta;
			edges[trace[u] ^ 1].flow -= delta;
		}
		totFlow += delta;
		totCost += delta * dist[t];
	}
	return make_pair(totFlow, totCost);
}

bool saturating(int s, int t) {
    getFlow(s, t);
    for (int &id: adj[s]) if (!edges[id].saturating()) return false;
    return true;
}

void dfs(int u, vector <int> &paths) {
	if (u == N + 2) return;
	paths.push_back(u);
	for (int &id: adj[u]) if (edges[id].flow == 1) {
		--edges[id].flow;
		dfs(edges[id].to, paths);
		return;
	}
}

int main(void) {
	ios_base::sync_with_stdio(false); cin.tie(nullptr); // cout.tie(nullptr);
	file("WALK");
	cin >> N >> M;
	int source = N + 1, sink = N + 2;
	adj.assign(N + 5, vector <int> ());
	dist.assign(N + 5, 0);
	trace.assign(N + 5, 0);
	addEdge(source, 1, 2, 0);
	addEdge(N, sink, 2, 0);
	while (M--) {
		int u, v, w; cin >> u >> v >> w;
		addEdge(u, v, 1, w);
		addEdge(v, u, 1, w);
	}
	pair <long long, long long> res = getFlow(source, sink);
	if (res.fi != 2) return !(cout << -1);
	cout << res.se << '\n';
	vector <int> path1, path2;
	dfs(1, path1);
	dfs(1, path2);
	reverse(path2.begin(), path2.end());
	path1.pop_back();
	for (int &x: path1) cout << x << ' ';
	for (int &x: path2) cout << x << ' ';
	cerr << "Time elapsed: " << TIME << " s.\n";
	return 0;
}
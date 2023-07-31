#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "scc";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
struct E {
	int u, v, w;
	E(int u, int v, int w): u(u), v(v), w(w) {}
	bool operator < (const E& e) const {
		return w < e.w;
	}
};
const int N = 3000 + 5;
vector<int> G[N];
int tin[N], low[N];
vector<E> edg;
int n, m;
stack<int> st;
int scc, t;
void dfs(int u) {
	tin[u] = low[u] = ++t;
	st.push(u);
	for (int v : G[u]) {
		if (tin[v]) 
			low[u] = min(low[u], tin[v]);
		else 
			dfs(v),
			low[u] = min(low[u], low[v]);
	}
	if (tin[u] == low[u]) {
		scc++; int v;
		do {
			v = st.top(); st.pop();
			tin[v] = low[v] = n + 1;
			// add v vao scc hien tai
		} while (v != u);
	}
}
int check(int l, int r) {
	for (int i = l; i <= r; ++i)
		G[edg[i].u].emplace_back(edg[i].v);
	t = 0, scc = 0;
	memset(low, 0, sizeof(low));
	memset(tin, 0, sizeof(tin));
	for (int i = 0; i < n; ++i)
		if (!tin[i]) dfs(i);
	for (int i = 0; i < n; ++i) G[i].clear();
	return scc == 1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n >> m;
	for (int i = 0, u, v, w; i < m; ++i)
		cin >> u >> v >> w, u--, v--,
		edg.emplace_back(u, v, w);
	sort(edg.begin(), edg.end());
	if (n == 1) 
		return cout << 0, 0;
	if (!check(0, m-1))
		return cout << -1, 0;
	int res = edg[m-1].w - edg[0].w;
	for (int i = 0, j = 0; i < m; ++i) {
		while (j < m && !check(i, j)) j++;
		if (j == m) break;
		res = min(res, edg[j].w - edg[i].w);
	}
	cout << res;
	return 0;
}


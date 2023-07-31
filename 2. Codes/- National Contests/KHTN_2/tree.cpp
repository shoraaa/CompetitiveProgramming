#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e5;
struct C {
	int v, i;
	C(int v, int i): v(v), i(i) {}
};
struct E {
	int u, v, w;
	E(int u, int v, int w): u(u), v(v), w(w) {}
};
vector<E> e;
int n, m;
int dfs_find(int u, int v) {
	vector<vector<C>> G(n);
	for (int i = 0; i < e.size(); ++i) {
		int u = e[i].u, v = e[i].v;
		G[u].emplace_back(v,i),
		G[v].emplace_back(u, i);
	}
	queue<int> q; 
	vector<int> vis(n); vis[u] = 1;
	vector<int> res(n);
	for (C& c : G[u]) q.emplace(c.v), res[c.v] = c.i, vis[c.v] = 1;
	while (!q.empty()) {
		int u = q.front(); q.pop(); vis[u] = 1;
		for (C& c : G[u]) if (!vis[c.v]) 
			res[c.v] = e[c.i].w > e[res[u]].w ? c.i : res[u], q.emplace(c.v);
	}
	return res[v];
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n; ll cur = 0;
	for (int i = 0, u, v, w; i < n-1; ++i)
		cin >> u >> v >> w, u--, v--, 
		e.emplace_back(u, v, w),
		cur += w;
	cin >> m;
	for (int i = 0, u, v, w; i < m; ++i) {
		cin >> u >> v >> w, u--, v--;
		int e_i = dfs_find(u, v);
		if (e[e_i].w > w) {
			e.erase(e.begin() + e_i);
			e.emplace_back(u, v, w);
			cur = cur - e[e_i].w + w; 
		}
		cout << cur << '\n';
	}
	return 0;
}


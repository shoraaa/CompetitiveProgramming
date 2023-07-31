#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "biconnected";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 25 * 1e4 + 5;
struct C {
	int v, i;
	C(int v = 0, int i = 0): v(v), i(i) {}
};
vector<C> G[N];
vector<int> leaf;
vector<pair<int, int>> bri;
int vis[N], tin[N], low[N], lin[N], siz[N];
int n, m, t = 0;
int find(int u) {
	if (u == lin[u]) return u;
	return lin[u] = find(lin[u]);
}
void unite(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return;
	if (siz[u] < siz[v]) swap(u, v);
	lin[v] = u; siz[u] += siz[v];
}
void find_bridges(int u, int e = -1) {
	vis[u] = 1;
	tin[u] = low[u] = t++;
	for (C& c : G[u]) if (c.i != e) {
		if (vis[c.v]) 
			unite(u, c.v),
			low[u] = min(low[u], tin[c.v]);
		else {
			find_bridges(c.v, c.i);
			low[u] = min(low[u], low[c.v]);
			if (low[c.v] <= tin[u]) unite(u, c.v);
			else bri.emplace_back(u, c.v);
		}
	}
}
void find_leaf(int u, int p = -1) {
	bool lf = 1;
	for (C& c : G[u]) if (c.v != p)
		find_leaf(c.v, u), lf = 0;
	if (lf) leaf.emplace_back(u);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();				
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 0, u, v; i < m; ++i)
			cin >> u >> v, u--, v--,
			G[u].emplace_back(v, i),
			G[v].emplace_back(u, i);
		bri.clear(); t = 0;
		for (int i = 0; i < n; ++i)
			lin[i] = i, siz[i] = 1, vis[i] = 0;
		for (int i = 0; i < n; ++i) 
			if (!vis[i]) find_bridges(i);
		
		for (int i = 0; i < n; ++i)
			vector<C>().swap(G[i]);
			
		if (bri.size() <= 1) {
			if (bri.size() == 0) 	
				cout << 0 << '\n';
			else
				cout << 1 << '\n' << 
				bri[0].first + 1 << ' ' << bri[0].second + 1 << '\n';
			continue;
		} 

		for (auto& p : bri) 
			G[find(p.first)].emplace_back(find(p.second)),
			G[find(p.second)].emplace_back(find(p.first));
		int r = 0;
		while (G[r].size() <= 1) r++;
		
		leaf.clear();
		find_leaf(r);
		int v = leaf.size();
		cout << (v + 1) / 2 << '\n';
		for (int i = 0; i < v / 2; ++i)
			cout << leaf[i]+1 << ' ' << leaf[v/2+i]+1 << '\n';
		if (v & 1) cout << leaf[v-1]+1 << ' ' << r+1 << '\n'; 
		for (int i = 0; i < n; ++i)
			vector<C>().swap(G[i]);
	}
	return 0;
}

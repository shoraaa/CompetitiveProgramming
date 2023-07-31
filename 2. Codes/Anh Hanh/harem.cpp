#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "harem";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3e5 + 5;
int deg[N];
vector<int> G[N];
vector<pair<int, int>> edg;
int n, m;
vector<int> cur, res;
int check(int mid) {
	for (int i = 0; i < n; ++i) 
		G[i].clear();
	memset(deg, 0, sizeof(deg));
	for (int i = 0; i <= mid; ++i) 
		G[edg[i].first].emplace_back(edg[i].second),
		deg[edg[i].second]++;
	
	// topo sort duoc va cung nam trong 1 tplt
	queue<int> q;
	int starter = -1;
	for (int u = 0; u < n; ++u) if (deg[u] == 0) {
		if (starter != -1) return 0;
		starter = u;
	}
	q.emplace(starter);
	cur.clear();
	while (!q.empty()) {
		int u = q.front(); q.pop();
		cur.emplace_back(u);
		int nxt = -1;
		for (int v : G[u]) {
			deg[v]--;
			if (deg[v] == 0) {
				if (nxt != -1) return 0;
				nxt = v;
			}
		}
		if (nxt != -1) q.emplace(nxt);
	}
	if (cur.size() != n) return 0;
	res = cur;
	return 1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n >> m;
	for (int i = 0, u, v; i < m; ++i)
		cin >> u >> v, u--, v--,
		edg.emplace_back(u, v);
	
	if (!check(m-1)) 
		return cout << -1, 0;
		
	int lo = 0, hi = m-1, mid, ans = m-1;
	while (lo <= hi) {
		mid = (lo + hi) >> 1;
		if (check(mid))
			ans = mid,
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	cout << ans + 1 << '\n';
	for (int i = 0; i < n; ++i)
		cout << res[i] + 1 << ' ';
	
	return 0;
}


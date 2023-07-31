/*
 * Author :  shora
 */
#include <bits/stdc++.h>
#define print(_v) for (auto &_ : _v) {cerr << _ << ' ';} cerr << endl;
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "dddd";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3e5 + 5;
vector<int> G[N];
int vis[N], siz[N],  dep[N], res[N], cnt[64];
int n, p;
void find_siz(int u, int e = -1) {
	siz[u] = 1;
	for (int v : G[u]) if (v != e && !vis[v]) {
		find_siz(v, u);
		siz[u] += siz[v];
	}
}
int centroid(int s, int u, int e = -1) {
	for (int v : G[u]) if (v != e && !vis[v])
		if (siz[v] > s / 2)
			return centroid(s, v, u);
	return u;
}
int r, cur_r;
void get(int u, int e) {
	dep[u] = dep[e] + 1;
	int d = -dep[u] % p;
	if (d < 0) d += p;
	res[u] += cnt[d];
	if (dep[u] % p == 0) cur_r++;
	//printf("GET %d += cnt[%d] = %d\n", u+1, d, cnt[d]);
	for (int v : G[u]) if (v != e && !vis[v]) 
		get(v, u);
}
void update(int u, int e) {
	int d = dep[u] % p;
	if (d >= p) d -= p;
	cnt[d]++;
	//printf("UPDATE %d, %d? ++\n", u+1, d);
	for (int v : G[u]) if (v != e && !vis[v]) {
		update(v, u);
	}
}
void solve(int u) {
	find_siz(u);
	u = centroid(siz[u], u);
	vis[u] = 1;
	//printf("CENTROID %d\n", u+1);
	dep[u] = 0;
	r = u, cur_r = 0;
	memset(cnt, 0, sizeof(cnt));
	cnt[0] = 1;
	for (int v : G[u]) if (!vis[v]) 
		get(v, u),
		update(v, u);
	reverse(G[u].begin(), G[u].end());
	memset(cnt, 0, sizeof(cnt));
	for (int v : G[u]) if (!vis[v]) 
		get(v, u),
		update(v, u);
	res[u] += cur_r / 2;
	for (int v : G[u]) if (!vis[v])
		solve(v);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();				
	cin >> n >> p;
	for (int i = 0, u, v; i < n-1; ++i) 
		cin >> u >> v, u--, v--,
		G[u].push_back(v),
		G[v].push_back(u);
	solve(0);
	for (int i = 0; i < n; ++i)
		cout << res[i] + 1 << ' ';
	find_siz(0);
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
void file() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	const string FILE_NAME = "tournament";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 3e5 + 5;
int lin[N], siz[N], nxt[N], ans[N];
int find(int u) {
	if (u == lin[u]) return u;
	return lin[u] = find(lin[u]);
}
void unite(int u, int v) {
	u = find(u), v = find(v);
	int unpainted = nxt[v];
	if (siz[u] > siz[v]) swap(u, v);
	lin[u] = v, siz[v] += siz[u], nxt[v] = unpainted;
}
int n, m;
int main() {
	//file();
	cin >> n >> n >> m;
	for (int i = 1; i <= n + 1; ++i)
		lin[i] = i, siz[i] = 1, nxt[i] = i;
	for (int i = 0, l, r, w; i < m; ++i) {
		cin >> l >> r >> w;
		for (int i = nxt[find(l)]; i <= w-1; i = nxt[find(i)])
			ans[i] = w, unite(i, i+1);
		for (int i = nxt[find(w+1)]; i <= r; i = nxt[find(i)])
			ans[i] = w, unite(i, i+1);
	}
	for (int i = 1; i <= n; ++i)
		cout << ans[i] << ' ';
}

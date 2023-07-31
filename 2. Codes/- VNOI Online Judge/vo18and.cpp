#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5, K = 30;
int a[N], G[K][K], b[K];
int n, q, z = 0;
void insert(int x) {
	vector<int> c;
	for (int i = 0; i < K; ++i)
		if (x >> i & 1) c.emplace_back(i), b[i]++;
	for (int i = 1; i < c.size(); ++i)
		G[c[i]][c[0]]++;
	if (x == 0) z++;
}
void erase(int x) {
	vector<int> c;
	for (int i = 0; i < K; ++i)
		if (x >> i & 1) c.emplace_back(i), b[i]--;
	for (int i = 1; i < c.size(); ++i)
		G[c[i]][c[0]]--;
	if (x == 0) z--;
}
int lin[K], cc;
int find(int u) {
	if (u == lin[u]) return u;
	return lin[u] = find(lin[u]);
}
void unite(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return;
	lin[v] = u, cc--;
}
int get() {
	vector<int> c;
	for (int i = 0; i < K; ++i)
		if (b[i]) lin[i] = i, c.emplace_back(i);
	cc = c.size();
	for (int i = 0; i < c.size(); ++i)
		for (int j = 0; j < i; ++j)
			if (G[c[i]][c[j]]) unite(c[i], c[j]);
	return cc + z;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i], insert(a[i]);
	cin >> q;
	char c;
	for (int i = 0, x, y; i < q; ++i) {
		cin >> c;
		if (c == '?') cout << get() << '\n';
		else cin >> x >> y, x--, erase(a[x]), a[x] = y, insert(a[x]);
	} 
	return 0;
}


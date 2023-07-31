#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "aquarium";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 2e6 + 5;
int li[N], cc;
int find(int u) {
	if (u == li[u]) return u;
	return li[u] = find(li[u]);
}
int unite(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return 0;
	li[v] = u; cc--;
	return 1;
}
string s[N];
vector<int> a[N];
int n, m;
struct E {
	int u, v, i, j;
	E(int u, int v, int i, int j): u(u), v(v), i(i), j(j) {}
	bool operator < (E& e) const {
		return a[i][j] < a[e.i][e.j];
	}
};
inline int d(int r, int c, int k) {
	return r*m+c + (k ? n*m : 0);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
			cin >> s[i];
	for (int i = 0; i < n; ++i) {
		a[i].resize(m);
		for (int j = 0; j < m; ++j)
			cin >> a[i][j];
		}
	// voi moi o ta co 2 dinh tu trai sang phai la i*m+j va i*m+j + nm
	for (int i = 0; i < n*m*2; ++i) li[i] = i; 
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		if (s[i][j] == '/') {
			if (j < m-1) unite(d(i, j, 1), d(i, j+1, 0));
			if (i < n-1) {
				if (s[i+1][j] == '/') unite(d(i, j, 1), d(i+1, j, 0));
				else unite(d(i, j, 1), d(i+1, j, 1));
			}
		} else { /* \ */ 
			if (j < m-1) unite(d(i, j, 1), d(i, j+1, 0));
			if (i < n-1) {
				if (s[i+1][j] == '/') unite(d(i, j, 0), d(i+1, j, 0));
				else unite(d(i, j, 0), d(i+1, j, 1));
			}
		}
	}
	
	vector<E> edges; edges.reserve(n*m*2);
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
		int u = find(d(i, j, 0)), v = find(d(i, j, 1));
		if (u != v) edges.emplace_back(u, v, i, j);
		}
	sort(edges.begin(), edges.end());
	
	cc = 0;
	for (int i = 0; i < n*m*2; ++i) 
		cc += li[i] == i, li[i] = i;
	ll res = 0;
	for (auto edge : edges) {
		if (unite(edge.u, edge.v)) 
			s[edge.i][edge.j] = '.', res += a[edge.i][edge.j]; 
		if (cc == 1) break;
	}
	cout << res << '\n';
	for (int i = 0; i < n; ++i) 
		cout << s[i] << '\n';
	return 0;
}



#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "FILE_NAME";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
struct C {
	int v, w;
	C(int v, int w): v(v), w(w) {}
};
struct S {
	int u;
	ll d;
	S(int u, ll d): u(u), d(d) {}
	bool operator < (const S& s) const {
		return d > s.d;
	}
};
const	int N = 3e5 + 5, M = 998244353;
vector<C> G[N];
ll dis[N];
ll pw(ll x, ll k) {
	ll res = 1;
	for (; k; k >>= 1, x = x * x % M) 
		if (k & 1) res = res * x % M;
	return res;
}
int n, k, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	cin >> n >> k >> m;
	for (int i = 0, u, t, h; i < k; ++i) {
		cin >> t >> h;
		while (t--)
			cin >> u, u--, 
			G[n + i].emplace_back(u, 0),
			G[u].emplace_back(n + i, h);
	}
	for (int i = 0, u, v, w; i < m; ++i) 
		cin >> u >> v >> w, u--, v--,
		G[u].emplace_back(v, w),
		G[v].emplace_back(u, w);
	int z;
	cin >> z;
	priority_queue<S> q;
	vector<ll> res(n);
	for (int i = 0; i < z; ++i) {
		memset(dis, -1, sizeof(dis));
		q.emplace(i, 0);
		dis[i] = 0;
		while (!q.empty()) {
			auto s = q.top(); q.pop();
			if (s.d != dis[s.u]) continue;
			for (C& c : G[s.u]) if (dis[c.v] == -1 || s.d + c.w < dis[c.v])
				dis[c.v] = s.d + c.w, q.emplace(c.v, dis[c.v]);
		}
		ll p = pw(i + 1, i + 1);
		for (int j = 0; j < n; ++j) {
			res[j] += p * dis[j] % M;
			if (res[j] >= M) res[j] -= M;
			if (res[j] < 0) res[j] += M;
		}
	}
	for (int i = 0; i < n; ++i)
		cout << res[i] << ' ';
	return 0;
}


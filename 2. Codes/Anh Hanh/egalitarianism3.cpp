#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "egalitarianism3";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 50 + 5;
struct C {
	int v, w;
	C(int v, int w): v(v), w(w) {}
};
vector<C> G[N];
int n;
set<int> res;
map<int, int> dfs_get(int u, int e) {
	map<int, int> res, nxt;
	res[0] = u;
	for (C& c : G[u]) if (c.v != e) {
		nxt = dfs_get(c.v, u);
		for (auto& x : nxt)  
			res[x.first + c.w] = x.second;
	}
	return res;
}
void dfs_try(int u, int e, map<int, int>& setp) {
	map<int, set<int>> cur;
	map<int, int> setv;
	for (C& c : G[u]) if (c.v != e) {
		setv = dfs_get(c.v, u);
		for (auto& x : setv) 
			cur[x.first + c.w].insert(x.second);
	}
	
	for (auto& x : setp) 
		cur[x.first].insert(x.second);
	
	for (auto& p : cur) if (p.second.size() > res.size())
		res = p.second;
	
	map<int, int> nxt;
	for (C& c : G[u]) if (c.v != e) {
		setv = dfs_get(c.v, u);
		for (auto& x : setv) 
			cur[x.first + c.w].erase(x.second);

		nxt.clear(); nxt[0] = c.v;
		for (auto& p : cur) if (!p.second.empty())
			nxt[p.first + c.w] = *p.second.begin();
		dfs_try(c.v, u, nxt);
		
		for (auto& x : setv) 
			cur[x.first + c.w].insert(x.second);
	}
	
	for (auto& x : setp) 
		cur[x.first].erase(x.second);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	file();
	cin >> n;
	for (int i = 0, u, v, w; i < n-1; ++i)
		cin >> u >> v >> w, u--, v--,
		G[u].emplace_back(v, w),
		G[v].emplace_back(u, w);
	if (n == 1) 
		return cout << 1 << ' ' << 1, 0;
	res = {0, 1};
	
	map<int, int> setp; setp[0] = 0;
	dfs_try(0, -1, setp);
	cout << res.size() << '\n';
	for (int x : res)
		cout << x + 1 << ' ';
	return 0;
}
 
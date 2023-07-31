#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "wedding";
	if (!fopen((FILE_NAME + ".inp").c_str(), "r")) return;
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
#define int ll
const int N = 3e5 + 5;
vector<int> adj[N];
int inb[N], far[N], dep[N], par[N], low[N], high[N];
int n, a, b;
void build(int u, int p = -1) {
  inb[u] = u == b, far[u] = 1; par[u] = p;
  for (int v : adj[u]) if (v != p) {
    dep[v] = dep[u] + 1;
    build(v, u);
    inb[u] |= inb[v]; 
    if (!inb[v]) far[u] = max(far[u], far[v] + 1);
  }
}
signed main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0); file();
  cin >> n;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  cin >> a >> b, a--, b--,
  build(a);
  int res = 0; vector<int> path;
  for (int v = b; v != -1; v = par[v]) 
    path.emplace_back(v);
  low[0] = far[b], high[path.size() - 1] = far[a];
  for (int i = 1; i < path.size() - 1; ++i)
    low[i] = max(low[i-1], far[path[i]] + i);
  for (int i = path.size() - 2; i; --i)
    high[i] = max(high[i+1], far[path[i]] + int(path.size()) - i - 1);
  for (int i = 1; i < path.size(); ++i)
    cerr << low[i-1] << ' ' << high[i] << '\n';
  for (int i = 1; i < path.size(); ++i)
    res = max(res, min(low[i-1], high[i]));
  cout << res;
	return 0;
}


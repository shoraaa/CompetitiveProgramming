#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5, inf = 1e9, M = 1e9 + 7;
vector<int> adj[N];
int a[N], val[N], in[N], low[N];
int n, m, t = 0;
ll res = 0, cnt = 1;
stack<int> st;
void dfs(int u) {
  low[u] = in[u] = ++t;
  st.emplace(u);
  for (int v : adj[u]) 
    if (in[v]) low[u] = min(low[u], in[v]);
    else dfs(v), low[u] = min(low[u], low[v]);
  if (low[u] == in[u]) {
    int v; pair<int, int> cur = {inf, 0};
    do {
      v = st.top(); st.pop(); 
      if (a[v] < cur.first) cur = {a[v], 1};
      else if (a[v] == cur.first) cur.second++;
      in[v] = low[v] = inf;
    } while (v != u);
    cnt = ll(cnt) * cur.second % M;
    res += cur.first;
  }
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("checkpost.inp", "r"))
    freopen("checkpost.inp", "r", stdin),
    freopen("checkpost.out", "w", stdout);
  cin >> n;
  for (int v = 0; v < n; ++v)
    cin >> a[v];
  memset(val, 0x3f, sizeof(val));
  cin >> m;
  for (int i = 0, u, v; i < m; ++i)  
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v);
  for (int v = 0; v < n; ++v) 
    if (!in[v]) dfs(v);
  cout << res << ' ' << cnt << '\n';
	return 0;
}


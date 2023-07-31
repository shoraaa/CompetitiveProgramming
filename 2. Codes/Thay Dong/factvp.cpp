#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, M = 1e6 + 1;
const ll inf = 1e18;
vector<int> adj[N], tmp[N], vert[M];
int lp[M], check[N], vis[N], a[N]; ll b[N];

ll res = -inf;

int par[N];
void build(int u, int p = -1) {
  par[u] = p;
  for (int v : adj[u]) if (v != p)
    build(v, u);
}

vector<ll> dfs(int u, int p = -1) {
  vis[u] = 1;
  vector<ll> cur(4, -inf); 
  cur[1] = b[u]; cur[0] = 0;
  for (int v : tmp[u]) if (v != p) {
    vector<ll> nxt = cur, add = dfs(v, u);
    nxt[1] = max(nxt[1], add[1] + b[u]);
    nxt[2] = max(nxt[2], add[1] + cur[1] + cur[1] + add[1] + b[u]);
    nxt[2] = max(nxt[2], add[2] + b[u] * 2);
    nxt[3] = max(nxt[3], add[1] * 2 + cur[2]);
    nxt[3] = max(nxt[3], add[2] + cur[1] * 2);
    cur = nxt;
  }
  res = max(res, cur[3]);
  return cur;
}

int n;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; int m = 0;
  for (int i = 0; i < n; ++i)
    cin >> b[i];
  for (int i = 0; i < n; ++i) 
    cin >> a[i], m = max(m, a[i]);
  vector<int> pr; 
  for (int i = 2; i * i <= m; ++i) if (!lp[i])
    for (int j = i * i; j <= m; j += i) lp[j] = i;
    
  for (int i = 2; i <= m; ++i) if (!lp[i])
    lp[i] = i, pr.emplace_back(i);

  for (int i = 0; i < n; ++i) {
    while (a[i] > 1) {
      int x = lp[a[i]];
      vert[x].emplace_back(i);
      while (a[i] % x == 0) a[i] /= x;
    }
  }

  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);

  build(0, -1);

  for (int x = 2; x <= m; ++x) if (vert[x].size() >= 3) {
    
    for (int u : vert[x]) check[u] = 1, vis[u] = 0;
    
    for (int u : vert[x]) if (~par[u] && check[par[u]])
      tmp[u].emplace_back(par[u]),
      tmp[par[u]].emplace_back(u);
    
    for (int u : vert[x]) if (!vis[u]) dfs(u);
    
    for (int u : vert[x]) tmp[u].clear(), check[u] = 0;
    
  }
  if (res < -1e11) cout << "No Solution";
  else cout << res;
  
	return 0;
}


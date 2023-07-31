#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 150005;
vector<int> adj[N];

struct Edge {
  int u, v;
  Edge(int u = 0, int v = 0): u(u), v(v) {}
} edges[N];

int n, q;

const int MOD = (int)1e9 + 19972207;
int seed, mul, add;
int getRandom(int n) {
  seed = (1LL * mul * seed + add) % MOD;
  return 1 + seed % n; 
}

int in[N], out[N], dep[N], t = 0;

int is_anscestor(int u, int p) {
  return in[u] >= in[p] && out[u] <= out[p];
}

void dfs(int u = 1, int p = 0) {
  dep[u] = dep[p] + 1;
  in[u] = t++;
  for (int v : adj[u]) 
    if (v != p) dfs(v, u);
  out[u] = t-1;
}


int e1, u1, v1, e2, u2, v2;
int tplt(int u) {
  if (is_anscestor(u, edges[e1].v)) return 1;
  else if (is_anscestor(u, edges[e2].v)) return 2;
  return 3;
}

int query() {
  if (dep[edges[e1].v] <= dep[edges[e2].v]) swap(e1, e2);
  if (tplt(u1) != tplt(v1) && tplt(u2) != tplt(v2)) {
    return 0;
  } else if (tplt(u1) == tplt(v1) && tplt(u2) == tplt(v2)) {
    return 2;
  } else {
    return 1;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int task; cin >> task;
  cin >> n;
  for (int i = 1, u, v; i <= n-1; ++i)
    cin >> u >> v,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u), 
    edges[i] = {u, v};
  
  dep[0] = -1, dfs();
  for (int i = 1; i <= n-1; ++i)
    if (dep[edges[i].v] <= dep[edges[i].u]) swap(edges[i].u, edges[i].v);
  
  cin >> q >> seed >> mul >> add;
  
  int res = 0;
  for (int i = 1; i <= q; ++i) {
    e1 = getRandom(n - 1);
    u1 = getRandom(n), v1 = getRandom(n);
    
    e2 = getRandom(n - 1);
    u2 = getRandom(n), v2 = getRandom(n);
    
    int tmp = e1 == e2 || u1 == v1 || u2 == v2
            ? MOD - 1 : query();

    res = (227LL * res + tmp) % MOD;
  }
  cout << res;
  
	return 0;
}


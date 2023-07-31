#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
vector<int> adj[N];
int n;

int bit[N];
int get(int i) {
  int res = 0;
  for (; i; i -= i & -i)
    res += bit[i];
  return res;
}

void update(int i, int v) {
  for (; i <= n; i += i & -i)
    bit[i] += v;
}

vector<int> leaf;
int dep[N], in[N], out[N], par[N][20], t = 0;
void dfs(int u = 0, int p = -1) {
  if (adj[u].size() == 1 && p != -1) leaf.emplace_back(u);
  in[u] = ++t;
  for (int v : adj[u]) if (v != p) {
    dep[v] = dep[u] + 1;
    par[v][0] = u;
    for (int i = 1; i < 20; ++i)
      par[v][i] = par[par[v][i - 1]][i - 1];
    dfs(v, u);
  }
  out[u] = t;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0, u, v; i < n - 1; ++i)
    cin >> u >> v, u--, v--,
    adj[u].emplace_back(v),
    adj[v].emplace_back(u);
  dfs();
  sort(leaf.begin(), leaf.end(), [&](int u, int v) {
    return dep[u] < dep[v];
  });

  int res = 0;
  
  for (int u : leaf) {
    if (get(in[u]) > 0) continue; 
    int d = dep[u] / 2, p = u;
    for (int i = 19; ~i; --i) 
      if (d >> i & 1) p = par[p][i];
    res += 1;
    update(in[p], 1);
    update(out[p] + 1, -1);
  }
  
  cout << res;
	return 0;
}


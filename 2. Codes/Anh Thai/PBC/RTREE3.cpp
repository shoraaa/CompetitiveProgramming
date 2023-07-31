#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5;
vector<int> adj1[N], adj2[N];
int n;

int in[N], out[N], t = 1;

vector<int> node[N], bit[N];
void pre_add(int i, int j) {
  for (; i; i -= i & -i)
    node[i].emplace_back(j);
}

void add(int i, int j, int v) {
  for (; i; i -= i & -i) for (int z = upper_bound(node[i].begin(), node[i].end(), j)
     - node[i].begin(); z <= node[i].size(); z += z & -z) bit[i][z-1] += v;
}

int get(int i, int j) {
  int res = 0;
  for (; i <= n; i += i & -i) for (int z = upper_bound(node[i].begin(), node[i].end(), j)
     - node[i].begin(); z; z -= z & -z) res += bit[i][z-1];
  return res;
}

void dfs1(int u = 0, int p = -1) {
  in[u] = t++;
  for (int v : adj1[u]) if (v != p)
    dfs1(v, u);
  out[u] = t-1;
  pre_add(out[u], in[u]);
}

int ans[N];
void dfs2(int u = 0, int p = -1) {
  add(out[u], in[u], 1);
  ans[u] = get(out[u], in[u]); // <= in[u] && >= out[u]
  for (int v : adj2[u]) if (v != p)
    dfs2(v, u);
  add(out[u], in[u], -1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj1[u].emplace_back(v),
    adj1[v].emplace_back(u);
  for (int i = 0, u, v; i < n-1; ++i)
    cin >> u >> v, u--, v--,
    adj2[u].emplace_back(v),
    adj2[v].emplace_back(u);
  dfs1();
  for (int i = 1; i <= n; ++i)
    sort(node[i].begin(), node[i].end()),
    bit[i].resize(node[i].size()); 
  dfs2();
  for (int i = 0; i < n; ++i)
    cout << ans[i] << ' ';
	return 0;
}


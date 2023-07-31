#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int n, m, n0, n1, W;
int lin[N], cnt0[N], cnt1[N];

int find(int u) {
  if (u == lin[u]) return u;
  return lin[u] = find(lin[u]);
}

ll res = 0;
void unite(int u, int v, int w) {
  u = find(u), v = find(v);
  if (u == v) return;
  if (w == W) res += 1LL * cnt0[u] * cnt1[v] + 1LL * cnt1[u] * cnt0[v];
  lin[v] = u, cnt0[u] += cnt0[v], cnt1[u] += cnt1[v];
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("path.inp", "r"))
    freopen("path.inp", "r", stdin),
    freopen("path.out", "w", stdout);
  cin >> n >> m >> W >> n0 >> n1;
  vector<tuple<int, int, int>> edges;
  for (int i = 0, u, v, w; i < m; ++i)
    cin >> u >> v >> w, u--, v--,
    edges.emplace_back(w, u, v);
  sort(edges.begin(), edges.end());
  for (int i = 0, v; i < n0; ++i) cin >> v, v--, cnt0[v] = 1;
  for (int i = 0, v; i < n1; ++i) cin >> v, v--, cnt1[v] = 1;
  for (int i = 0; i < n; ++i) lin[i] = i;
  for (auto& p : edges) {
    int w, u, v; tie(w, u, v) = p;
    unite(u, v, w);
  }
  cout << res;
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 5;
int n, m, k, p;
int keep[N], lin[N], src[N];

int find(int u) {
  if (u == lin[u]) return u;
  return lin[u] = find(lin[u]);
}

int unite(int u, int v) {
  u = find(u), v = find(v);
  if (u == v) return 0;
  if (src[u] != -1 && src[v] != -1) return 0;
  if (src[u] == -1) lin[u] = v;
  else lin[v] = u;
  return 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("moji.inp", "r"))
    freopen("moji.inp", "r", stdin),
    freopen("moji.out", "w", stdout);
  int T; cin >> T;
  cin >> n;
  for (int i = 0; i < n; ++i)
    lin[i] = i, src[i] = -1;
  cin >> k;
  for (int i = 0, v; i < k; ++i)
    cin >> v, v--, src[v] = v;
  cin >> m;
  ll res = 0;
  vector<tuple<int, int, int, int>> edges;
  for (int i = 1, u, v, w; i <= m; ++i)
    cin >> u >> v >> w, u--, v--,
    edges.emplace_back(-w, -i, u, v), res += w;
  cin >> p;
  for (int i = 1, u, v, w; i <= p; ++i)
    cin >> u >> v >> w, u--, v--,
    edges.emplace_back(w, i, u, v);
  sort(edges.begin(), edges.end());
  int a = m; vector<int> build;
  for (auto& e : edges) {
    int u, v, t, w; tie(w, t, u, v) = e;
    if (unite(u, v)) {
      res += w;
      if (t < 0) keep[-t] = 1, a--;
      else build.emplace_back(t);
    }
  }
  cout << res * T << '\n';
  cout << a << '\n';
  for (int i = 1; i <= m; ++i) 
    if (!keep[i]) cout << i << ' ';
  cout << '\n' << build.size() << '\n';
  sort(build.begin(), build.end());
  for (int i : build) cout << i << ' ';
  
	return 0;
}


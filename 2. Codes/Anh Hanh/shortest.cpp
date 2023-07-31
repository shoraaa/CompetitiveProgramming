#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "shortest";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
struct edge {
  int u, v; ll w;
  edge(int u, int v, ll w): u(u), v(v), w(w) {}
  bool operator < (const edge& e) {
    return w < e.w;
  }
};
vector<edge> e;
const int N = 230;
int d[N][N], used[N*N];
ll cur[N][N];
int n, ans = 0;
inline ll dis(int u, int v) {
  if (u > v) swap(u, v);
  return cur[u][v];
}
int check(int x, int y, int w, int i) {
  if (cur[x][y] <= w) return 0;
  cur[x][y] = w; ans++, used[i] = 1;
  for (int u = 0; u < n; ++u)
    for (int v = u+1; v < n; ++v)
        cur[u][v] = min(cur[u][v], dis(u, x) + dis(x, v));
  for (int u = 0; u < n; ++u)
    for (int v = u+1; v < n; ++v)
        cur[u][v] = min(cur[u][v], dis(u, y) + dis(y, v));
  for (int u = 0; u < n; ++u)
    for (int v = u+1; v < n; ++v)
      if (cur[u][v] != d[u][v]) return 0;
  return 1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  file();
  cin >> n;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> d[i][j];
  e.reserve(n * (n - 1) / 2);
  for (int u = 0; u < n; ++u) for (int v = u+1; v < n; ++v)
    e.emplace_back(u, v, d[u][v]);
  sort(e.begin(), e.end());
  memset(cur, 0x3f, sizeof(cur));
  for (int u = 0; u < n; ++u) cur[u][u] = 0;
  for (int i = 0; i < e.size(); ++i)
    if (check(e[i].u, e[i].v, e[i].w, i)) break;
  cout << ans << '\n';
  for (int i = 0; i < e.size(); ++i) if (used[i])
    cout << e[i].u+1 << ' ' << e[i].v+1 << ' ' << e[i].w << '\n';
	return 0;
}


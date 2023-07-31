#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5000 + 5;
int z[N];
struct Edge {
  int u, v, w;
  Edge(int u, int v, int w): u(u), v(v), w(w) {}
};
vector<Edge> edges;
int n, m;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  // z[i] la so so 0 xet i thang dau tien
  // => 0 <= z[i] - z[i-1] <= 1
  // z[i] <= z[i-1] + 1; z[i-1] <= z[i] + w
  // (u, v, w): d[v] <= d[u] + w
  for (int i = 1; i <= n; ++i)
    edges.emplace_back(i-1, i, 1),
    edges.emplace_back(i, i-1, 0);
  for (int i = 0, l, r, k, v; i < m; ++i) {
    cin >> l >> r >> k >> v;
    if (v == 0) {
      // z[l] <= z[r+1] - k
      edges.emplace_back(r+1, l, -k);
    } else {
      // z[r+1] <= z[l] + k-1
      edges.emplace_back(l, r+1, k-1);
    }
  }
  memset(z, 0x3f, sizeof(z)); z[0] = 0;
  for (int i = 0; i < n; ++i) for (auto& e : edges)
    if (z[e.u] + e.w < z[e.v]) z[e.v] = z[e.u] + e.w;
  for (auto& e : edges)
    if (z[e.u] + e.w < z[e.v]) 
      return cout << -1, 0;
  for (int i = 1; i <= n; ++i)
    cout << !(z[i]-z[i-1]) << ' ';
	return 0;
}


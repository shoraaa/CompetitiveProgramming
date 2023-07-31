#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1.5e4 + 5;
struct Edge {
  int u, v, w;
  bool operator < (const Edge& e) const {
    return w < e.w;
  }
} ed[N];
int n, m;

int lin[N], siz[N];
int find(int i) {
  if (i == lin[i]) {
    return i;
  }
  return lin[i] = find(lin[i]);
}

int unite(int u, int v) {
  u = find(u); v = find(v);
  if (u == v) {
    return 0;
  }
  
  if (siz[u] < siz[v]) {
    swap(u, v);
  }
  
  lin[v] = u; siz[u] += siz[v];
  return 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    cin >> ed[i].u >> ed[i].v >> ed[i].w;
  }
  
  sort(ed + 1, ed + m + 1);
  
  for (int i = 1; i <= n; ++i) {
    lin[i] = i; siz[i] = 1;
  }
  
  int res = 0;
  for (int i = 1; i <= m; ++i) {
    if (unite(ed[i].u, ed[i].v)) {
      res += ed[i].w;
    }
  }
  cout << res;
  
	return 0;
}


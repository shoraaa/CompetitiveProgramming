#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5005;
int dis[2][N * N], bad[N * N];
int n, m, rs, cs, rf, cf;

int dr[4] = {-1, 1, -1, 1}, dc[4] = {-1, 1, 1, -1}, dir[4] = {0, 0, 1, 1};

inline int pos(int r, int c) {
  return r * n + c;
}

int check(int r, int c) {
  return 0 <= r && r < n && 0 <= c && c < n && !bad[pos(r, c)];
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("bishop.inp", "r"))
    freopen("bishop.inp", "r", stdin),
    freopen("bishop.out", "w", stdout);
  cin >> n >> m;
  cin >> rs >> cs >> rf >> cf; rs--; cs--; rf--; cf--;
  for (int i = 0; i < m; ++i) {
    int r, c; cin >> r >> c; r--; c--;
    bad[pos(r, c)] = 1;
  }
  if (rs == rf && cs == cf)
    return cout << 0, 0;
  memset(dis, 0x3f, sizeof(dis));
  deque<pair<int, int>> q;
  for (int i = 0; i < 4; ++i) 
    if (check(rs + dr[i], cs + dc[i])) 
      dis[dir[i]][pos(rs + dr[i], cs + dc[i])] = 1,
      q.emplace_back(dir[i], pos(rs + dr[i], cs + dc[i]));
  while (!q.empty()) {
    auto p = q.front(); q.pop_front();
    int d = p.first, u = p.second, r = u / n, c = u % n;
    if (r == rf && c == cf) 
      return cout << dis[d][u], 0;
    for (int i = 0; i < 4; ++i) {
      int nd = dir[i], nr = r + dr[i], nc = c + dc[i];
      if (!check(nr, nc)) continue;
      int v = pos(nr, nc), w = d != nd;
      if (dis[d][u] + w < dis[nd][v]) {
        dis[nd][v] = dis[d][u] + w;
        if (w == 1) q.emplace_back(nd, v);
        else q.emplace_front(nd, v);
      }
    }
  }
  cout << -1;
	return 0;
}


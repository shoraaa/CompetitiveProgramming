#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 505;
int a[N][N], b[N][N], dis[N][N];
int n, m;

int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
int inside(int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < m;
}

int dijkstra(int c[][N]) {
  memset(dis, -1, sizeof(dis)); dis[0][0] = c[0][0]; 
  priority_queue<tuple<int, int, int>> q;
  q.emplace(-dis[0][0], 0, 0);
  while (!q.empty()) {
    int val, i, j; tie(val, i, j) = q.top(); q.pop();
    for (int d = 0; d < 4; ++d) {
      int x = i + dr[d], y = j + dc[d];
      if (inside(x, y) && !~dis[x][y])
        dis[x][y] = dis[i][j] + c[x][y],
        q.emplace(-dis[x][y], x, y);
    }
  }
  return dis[n-1][m-1];
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("sc.inp", "r"))
    freopen("sc.inp", "r", stdin),
    freopen("sc.out", "w", stdout);
  cin >> n >> m;
  for (int i = 0, x; i < n; ++i) for (int j = 0; j < m; ++j) {
    cin >> x;
    while (x % 2 == 0) x /= 2, a[i][j]++;
    while (x % 5 == 0) x /= 5, b[i][j]++;
  }
  cout << min(dijkstra(a), dijkstra(b));
	return 0;
}


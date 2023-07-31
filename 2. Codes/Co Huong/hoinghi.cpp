#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005, B = 1001;
int n, k;
int a[N][N], dis[N][N];

int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
ll res[2];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("hoinghi.inp", "r")) 
    freopen("hoinghi.inp", "r", stdin),
    freopen("hoinghi.out", "w", stdout);
  cin >> n >> k;
  int min_x = B, min_y = B, max_x = B, max_y = B;
  for (int i = 0, x, y; i < n; ++i) {
    cin >> x >> y; x += B, y += B;
    a[x][y] = 1;
    min_x = min(min_x, x), max_x = max(max_x, x);
    min_y = min(min_y, y), max_y = max(max_y, y);
  }
  min_x--, min_y--, max_x++, max_y++;
  auto inside = [&](int x, int y) {
    return min_x <= x && x <= max_x && min_y <= y && y <= max_y;
  };
  queue<pair<int, int>> q;
  memset(dis, -1, sizeof(dis));
  q.emplace(B, B); dis[B][B] = 0;
  while (!q.empty()) {
    int i, j; tie(i, j) = q.front(); q.pop();
    res[dis[i][j] & 1]++;
    if (dis[i][j] == k) continue;
    for (int d = 0; d < 4; ++d) {
      int x = i + dr[d], y = j + dc[d];
      if (!inside(x, y) || a[x][y] || ~dis[x][y]) continue;
      dis[x][y] = dis[i][j] + 1, q.emplace(x, y);
    }
  }

  for (int y = min_y + 1; y <= max_y - 1; ++y) {
    if (!~dis[min_x][y]) continue;
    int d = dis[min_x][y], col = d & 1;
    res[col] += (k - d) / 2;
    res[col^1] += (k - d + 1) / 2;
  }
  
  for (int y = min_y + 1; y <= max_y - 1; ++y) {
    if (!~dis[max_x][y]) continue;
    int d = dis[max_x][y], col = d & 1;
    res[col] += (k - d) / 2;
    res[col^1] += (k - d + 1) / 2;
  }
  
  for (int x = min_x + 1; x <= max_x - 1; ++x) {
    if (!~dis[x][min_y]) continue;
    int d = dis[x][min_y], col = d & 1;
    res[col] += (k - d) / 2;
    res[col^1] += (k - d + 1) / 2;
  }
  
  for (int x = min_x + 1; x <= max_x - 1; ++x) {
    if (!~dis[x][max_y]) continue;
    int d = dis[x][max_y], col = d & 1;
    res[col] += (k - d) / 2;
    res[col^1] += (k - d + 1) / 2;
  }
  
  if (~dis[min_x][min_y]) {
    int d = dis[min_x][min_y], col = d & 1;
    for (int i = 1; i <= k - d; ++i)
      res[col ^ (i & 1)] += i + 1;
  }
  
  if (~dis[min_x][max_y]) {
    int d = dis[min_x][max_y], col = d & 1;
    for (int i = 1; i <= k - d; ++i)
      res[col ^ (i & 1)] += i + 1;
  }
  
  if (~dis[max_x][min_y]) {
    int d = dis[max_x][min_y], col = d & 1;
    for (int i = 1; i <= k - d; ++i)
      res[col ^ (i & 1)] += i + 1;
  }
  
  if (~dis[max_x][max_y]) {
    int d = dis[max_x][max_y], col = d & 1;
    for (int i = 1; i <= k - d; ++i)
      res[col ^ (i & 1)] += i + 1;
  }
  
  cout << res[0] << ' ' << res[1];
  
	return 0;
}


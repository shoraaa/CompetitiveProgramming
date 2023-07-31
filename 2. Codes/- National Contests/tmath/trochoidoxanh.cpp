#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 5;
struct State {
  int i, j, d, t;
  State(int i, int j, int t, int d): i(i), j(j), d(d), t(t) {}
};
int di[4] = {-1, 0, 1, 0}, dj[4] = {0, 1, 0, -1};
int dis[N][N][2], a[N][N];
int n, m;
void update(int i, int j, int t, int v) {
  if (i < 0 || i >= n || j < 0 || j >= m || dis[i][j][t] != -1)
    return;
  dis[i][j][t] = v;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    cin >> a[i][j];
  queue<State> q;
  memset(dis, -1, sizeof(dis));
  q.emplace(0, 0, 0, 0);
  dis[0][0][0] = 0;
  
  auto update = [&](int i, int j, int t, int v) {
    if (i < 0 || i >= n || j < 0 || j >= m || dis[i][j][t] != -1)
      return;
    dis[i][j][t] = v;
    q.emplace(i, j, t, v);
  };
  
  while (!q.empty()) {
    auto s = q.front(); q.pop();
    int green = a[s.i][s.j] ^ s.t;
    update(s.i, s.j, s.t^1, dis[s.i][s.j][s.t] + 1);
    if (green) {
      if (s.i == n-1 && s.j == m-1)
        return cout << dis[s.i][s.j][s.t], 0;
      for (int k = 0; k < 4; ++k) 
        update(s.i+di[k], s.j+dj[k], s.t^1, dis[s.i][s.j][s.t] + 1);
    }
  }
	return 0;
}


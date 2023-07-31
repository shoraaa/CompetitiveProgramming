#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using Board = vector<vector<int>>;
const int N = 102;
Board s, t;
int row[N * N], col[N * N];
int n = 4, m = 4;
int h(const Board& a) {
  int ans = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) 
      ans += abs(i - row[a[i][j]]) + abs(j - col[a[i][j]]);
  return ans;
}
struct State {
  Board b; int d, r, c;
  State(Board& b, int d): b(b), d(d) {
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
      if (!b[i][j]) r = i, c = j;
  }
  bool operator < (const State& s) const {
    return d + h(b) > s.d + h(s.b);
  }
};
int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
int inside(int r, int c) {
  return 0 <= r && r < n && 0 <= c && c < m;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  //cin >> n >> m;
  t.resize(n, vector<int>(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      t[i][j] = i * m + j + 1,
      row[t[i][j]] = i, col[t[i][j]] = j;
  t[n-1][m-1] = 0; row[0] = n-1, col[0] = m-1;
  s.resize(n, vector<int>(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> s[i][j];
  priority_queue<State> q;
  map<Board, int> dis;
  map<Board, tuple<int, int, int>> to;
  q.emplace(s, 0);
  dis[s] = 0;
  while (!q.empty()) {
    auto s = q.top(); q.pop();
    if (s.d != dis[s.b]) continue;
    if (s.b == t) break;
    int r = s.r, c = s.c; 
    for (int d = 0; d < 4; ++d) if (inside(r + dr[d], c + dc[d])) {
      auto v = s.b;
      swap(v[r][c], v[r + dr[d]][c + dc[d]]);
      
      if (!dis.count(v) || s.d + 1 < dis[v]) 
        dis[v] = s.d + 1, 
        to[v] = make_tuple(r, c, d),
        q.emplace(v, s.d + 1);
    }
  }
  cout << dis[t] << '\n';
  auto v = t;
  int r, c, d;
  vector<int> ans;
  while (v != s) {
    tie(r, c, d) = to[v];
    ans.emplace_back(v[r][c]);
    swap(v[r][c], v[r + dr[d]][c + dc[d]]);
  }
  reverse(ans.begin(), ans.end());
  for (int x : ans) cout << x << ' ';
	return 0;
}


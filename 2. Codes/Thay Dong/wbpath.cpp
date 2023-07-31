#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3 + 5;
int a[N][N];
int n, m, sx, sy, tx, ty;

int inside(int r, int c) {
  return 0 <= r && r < n && 0 <= c && c < m;
}
int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
char dch[4] = {'U', 'R', 'D', 'L'};
int rev[4] = {2, 3, 0, 1};

int dp[N][N][4], tr[N][N][4];
int dif1() {
  int base = 1;
  queue<tuple<int, int, int>> q;
  memset(dp, 0, sizeof(dp));
  dp[sx][sy][a[sx][sy] + base] = 1;
  q.emplace(sx, sy, a[sx][sy]);
  int x, y, t;
  while (!q.empty()) {
    tie(x, y, t) = q.front(); q.pop();
    if (x == tx && y == ty && t == 0) {
      cout << dp[x][y][t + base] << ' ';
      string s;
      for (;;) {
        s += dch[tr[x][y][t + base]];
        int d = rev[tr[x][y][t + base]];
        t -= a[x][y]; x += dr[d]; y += dc[d];
        if (x == sx && y == sy) break;
      }
      reverse(s.begin(), s.end());
      cout << s << '\n';
      return 1;
    }
    for (int d = 0; d < 4; ++d) {
      int r = x + dr[d], c = y + dc[d];
      if (!inside(r, c)) continue;
      int w = t + a[r][c];
      if (w < -1 || w > 1) continue;
      if (!dp[r][c][w + base])
        dp[r][c][w + base] = dp[x][y][t + base] + 1,
        tr[r][c][w + base] = d,
        q.emplace(r, c, w);
    }
  }
  return 0;
}

string go(int x, int y, int u, int v, int& b, int& w) {
  string s;
  while (x < u) s += 'D', x++, b += a[x][y] == -1, w += a[x][y] == 1;
  while (x > u) s += 'U', x--, b += a[x][y] == -1, w += a[x][y] == 1;
  while (y < v) s += 'R', y++, b += a[x][y] == -1, w += a[x][y] == 1;
  while (y > v) s += 'L', y--, b += a[x][y] == -1, w += a[x][y] == 1;
  return s;
}
string loop(int x, int y, int t, int& b, int& w) {
  for (int d = 0; d < 4; ++d) {
    int r = x + dr[d], c = y + dc[d];
    if (inside(r, c) && a[r][c] == a[x][y]) {
      string s;
      for (int i = 0; i < t; ++i) {
        s += dch[d], s += dch[rev[d]];
        b += (a[r][c] == -1) * 2;
        w += (a[r][c] == 1) * 2;
      }
      return s;
    }
  }
  assert(0);
}

pair<int, int> pb, pw;
#define fi first
#define se second
int solve() {
  if ((sx + sy) % 2 == (tx + ty) % 2) return 0;
  if (dif1()) return 1;
  if (pb.fi == -1 || pw.fi == -1) return 0;
  int b = 0, w = 0, bx = pb.fi, by = pb.se, wx = pw.fi, wy = pw.se;
  if (a[sx][sy] == 1) w++; else b++;
  string x = go(sx, sy, bx, by, b, w);
  string y = go(bx, by, wx, wy, b, w);
  string z = go(wx, wy, tx, ty, b, w);
  assert((b - w) % 2 == 0); int cb = b, cw = w;
  if (cb > cw) y += loop(wx, wy, (cb - cw) / 2, b, w); 
  else if (cb < cw) x += loop(bx, by, (cw - cb) / 2, b, w);
  string res = x + y + z;
  cout << res.size() + 1 << ' ' << res << '\n';
  return 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; char c;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    cin >> c; 
    if (c == 'W') a[i][j] = 1;
    else a[i][j] = -1;
  }
  pb.fi = -1, pw.fi = -1;
  for (int x = 0; x < n; ++x) for (int y = 0; y < m; ++y) for (int d = 0; d < 4; ++d) {
    int r = x + dr[d], c = y + dc[d];
    if (inside(r, c) && a[x][y] == a[r][c]) {
      if (a[x][y] == -1) pb = {x, y};
      else pw = {x, y};
    }
  }
  
  int q; cin >> q;
  for (int nv = 0; nv < q; ++nv) { 
    cin >> sx >> sy >> tx >> ty,
    sx--, sy--, tx--, ty--;
    if (!solve()) 
      cout << -1 << '\n';
  }
	return 0;
}

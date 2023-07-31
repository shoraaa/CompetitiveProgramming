#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 305;
int dis[N][180][180], min_dis[N][180][180], trace[N][180][180];
pair<int, int> go[N][180][180];
string s[N], c;
int n, m;

#define fi first
#define se second

int mov_x[5] = {-1, 1, 0, 0, 0}, mov_y[5] = {0, 0, -1, 1, 0};
int rev_x[5] = {1, -1, 0, 0, 0}, rev_y[5] = {0, 0, 1, -1, 0};
char cha[5] = {'U','D', 'L', 'R', 'H'};

int inside(int x, int y) {
  return 1 <= x && x <= n && 1 <= y && y <= m && s[x][y] != '#';
}

int check(int i, int j, int k) {
  if (((i == 1 || s[i - 1][j] == '#') && c[k] == 0) || 
      ((i == n || s[i + 1][j] == '#') && c[k] == 1) || 
      ((j == 1 || s[i][j - 1] == '#') && c[k] == 2) || 
      ((j == m || s[i][j + 1] == '#') && c[k] == 3)) return 1;
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("dichuyen.inp", "r"))
    freopen("dichuyen.inp", "r", stdin),
    freopen("dichuyen.out", "w", stdout);
  
  // dis[i][j][k] = min(..dis[i][j][k'], dis[i*][j*][k-1], ..)
  
  int task; cin >> task;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> s[i], s[i] = ' ' + s[i];
  cin >> c; int l = c.size(); c = ' ' + c;
  for (int i = 1; i <= l; ++i) {
    if (c[i] == 'U') c[i] = 0;
    else if (c[i] == 'D') c[i] = 1;
    else if (c[i] == 'L') c[i] = 2;
    else if (c[i] == 'R') c[i] = 3;
    else c[i] = 4;
  }
  
  int sx, sy, ex, ey;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
    if (s[i][j] == 'S') sx = i, sy = j;
    else if (s[i][j] == 'E') ex = i, ey = j;
  
  memset(dis, 0x3f, sizeof(dis));
  int INF = dis[0][0][0];
  
  priority_queue<tuple<int, int, int>> q;
  dis[0][sx][sy] = 0; q.emplace(0, sx, sy);
  while (!q.empty()) {
    int d, i, j; tie(d, i, j) = q.top(); q.pop();
    if (-d != dis[0][i][j]) continue; d = -d;
    for (int ch = 0; ch < 4; ++ch) if (inside(i + mov_x[ch], j + mov_y[ch])) {
      if (d + 1 < dis[0][i + mov_x[ch]][j + mov_y[ch]]) {
        dis[0][i + mov_x[ch]][j + mov_y[ch]] = d + 1;
        go[0][i + mov_x[ch]][j + mov_y[ch]] = {3, ch};
        q.emplace(-(d + 1), i + mov_x[ch], j + mov_y[ch]);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      min_dis[0][i][j] = dis[0][i][j];
      trace[0][i][j] = 0;
    }
  }
  
  for (int k = 1; k <= l; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) if (s[i][j] != '#') {
        
        if (check(i, j, k)) 
          dis[k][i][j] = dis[k - 1][i][j],
          go[k][i][j] = {-1, 0};
        
        if (inside(i + rev_x[c[k]], j + rev_y[c[k]]) 
          && dis[k - 1][i + rev_x[c[k]]][j + rev_y[c[k]]] < dis[k][i][j])
            dis[k][i][j] = dis[k - 1][i + rev_x[c[k]]][j + rev_y[c[k]]],
            go[k][i][j] = {0, 0};
          
        for (int ch = 0; ch < 5; ++ch) if (inside(i + rev_x[ch], j + rev_y[ch])) {
          if (dis[k - 1][i + rev_x[ch]][j + rev_y[ch]] + 1 < dis[k][i][j]) {
             dis[k][i][j] = dis[k - 1][i + rev_x[ch]][j + rev_y[ch]] + 1; 
             go[k][i][j] = {1, ch};
          }
        }
        
        if (min_dis[k - 1][i][j] + 1 < dis[k][i][j]) {
          dis[k][i][j] = min_dis[k - 1][i][j] + 1;
          go[k][i][j] = {2, trace[k - 1][i][j]};
        }
          
        q.emplace(-dis[k][i][j], i, j);
        assert(dis[k][i][j] <= n*m);
      }
    }
    
    // for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if (dis[k][i][j] != INF) {
      // cerr << k << ' ' << i << ' ' << j << ' ' << dis[k][i][j] << '\n';
    // }

    while (!q.empty()) {
      int d, i, j; tie(d, i, j) = q.top(); q.pop();
      if (-d != dis[k][i][j]) continue; d = -d;
      for (int ch = 0; ch < 4; ++ch) if (inside(i + mov_x[ch], j + mov_y[ch])) {
        if (d + 1 < dis[k][i + mov_x[ch]][j + mov_y[ch]]) {
          dis[k][i + mov_x[ch]][j + mov_y[ch]] = d + 1;
          go[k][i + mov_x[ch]][j + mov_y[ch]] = {3, ch};
          q.emplace(-(d + 1), i + mov_x[ch], j + mov_y[ch]);
          assert(d + 1 <= n*m);
        }
      }
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) if (dis[k][i][j] < min_dis[k - 1][i][j]) {
        min_dis[k][i][j] = dis[k][i][j];
        trace[k][i][j] = k;
      } else {
        min_dis[k][i][j] = min_dis[k - 1][i][j];
        trace[k][i][j] = trace[k - 1][i][j];
      }
    }

  }
  cout << (dis[l][ex][ey] == INF ? -1 : dis[l][ex][ey]) << '\n';
  if (dis[l][ex][ey] == INF) return 0;
  
  int x = ex, y = ey, k = l;
  
  vector<pair<int, int>> path;
  for (;;) {
    if (k == 0 && x == sx && y == sy) break;
    auto p = go[k][x][y]; 
    if (p.fi == -1) {
      k -= 1; 
      path.emplace_back(-1, 0);
    } else if (p.fi == 0) {
      path.emplace_back(0, 0);
      x += rev_x[c[k]], y += rev_y[c[k]];
      k -= 1;
    } else if (p.fi == 1) {
      path.emplace_back(1, p.se);
      x += rev_x[p.se], y += rev_y[p.se];
      k -= 1;
    } else if (p.fi == 2) {
      path.emplace_back(2, k);
      k = p.se;
    } else if (p.fi == 3) {
      path.emplace_back(3, p.se);
      x += rev_x[p.se], y += rev_y[p.se];
    }
  }
  reverse(path.begin(), path.end());
  k = 0; x = 0, y = 0;
  int id = 0;
  for (auto& p : path) {
    if (p.fi == -1) {
      k += 1; id += 1;
    } else if (p.fi == 0) {
      k += 1; id += 1;
    } else if (p.fi == 1) {
      k += 1; id += 1;
      cout << "REP " << id << ' ' << cha[p.se] << '\n';
    } else if (p.fi == 2) {
      // xoa het moi so tu k+1 den p.se -> p.se-k so bi xoa 
      cout << "DEL " << id+1 << ' ' << id+p.se-k << '\n';
      k = p.se;
    } else if (p.fi == 3) {
      cout << "INS " << id << ' ' << cha[p.se] << '\n';
      id++;
    }
  }
  
  
  
	return 0;
}

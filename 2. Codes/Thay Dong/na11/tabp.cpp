#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct S {
  int i, j, v, dp;
  S(int i, int j, int v): i(i), j(j), v(v) {}
  bool operator < (const S& s) const {
    return v < s.v;
  }
};

const int N = 2505;
int a[N][N];
int n, m, d;


int t[2 * N][2 * N];
void modify_y(int x, int y, int value) {
  for (y += n, t[x][y] = max(t[x][y], value); y > 1; y >>= 1)
    t[x][y>>1] = max(t[x][y], t[x][y^1]);
}

void modify_x(int x, int y, int value) {  // set value at position x, y
  for (x += n; x >= 1; x >>= 1)
    modify_y(x, y, value);
}

int query_y(int x, int l, int r) {
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t[x][l++]);
    if (r&1) res = max(res, t[x][--r]);
  }
  return res;
}

int query_x(int l, int r, int y1, int y2) {  // sum on interval [l, r)
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, query_y(l++, y1, y2));
    if (r&1) res = max(res, query_y(--r, y1, y2));
  }
  return res;
}


int get(int i, int j) {
  // [i-d, j-d] -> [i+d][j+d]
  return query_x(max(0, i-d), min(i+d+1, n), max(0, j-d), min(j+d+1, n));
}

void update(int i, int j, int v) {
  modify_x(i, j, v);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> d;
  vector<S> pos; pos.reserve(n * m);
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    cin >> a[i + j][i - j + m - 1],
    pos.emplace_back(i, j, a[i + j][i - j + m - 1]);
  n = n + m - 1;
  sort(pos.begin(), pos.end());
  
  int res = 0;
  for (int i = 0; i < pos.size();) {
    int j = i;
    while (j < pos.size() && pos[j].v == pos[i].v) {
      pos[j].dp = get(pos[j].i + pos[j].j, pos[j].i - pos[j].j + m - 1) + 1;
      j++;
    }
    
    for (int k = i; k < j; ++k) {
      update(pos[k].i + pos[k].j, pos[k].i - pos[k].j + m - 1, pos[k].dp);
      res = max(res, pos[k].dp);
    }
    
    i = j;
  }
  
  cout << res;
    
	return 0;
}


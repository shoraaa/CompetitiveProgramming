#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1505;
int n;

int d1[N * 2][N * 2], d2[N * 2][N * 2];
inline void cmax(int& x, int y) { if (x < y) x = y; }

bitset<N * 2> col[4][N * 2];
int cnt = 0;
inline void paint(int x, int y, int c) {
  if (col[c][x][y]) return;
  col[c][x][y] = 1, cnt++;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; char c;
  for (int i = 0, x, y, d; i < n; ++i) {
    cin >> c >> x >> y >> d; x += N, y += N;
    if (c == 'A') cmax(d1[y - d / 2][x - d / 2], d);
    else cmax(d2[y - d / 2][x], d);
  }
  for (int y = 1; y < 2 * N - 2; ++y) for (int x = 1; x < 2 * N - 1; ++x) {
    if (d1[y][x]) {
      for (int i = 0; i < 4; ++i) paint(x, y, i);  
      int d = d1[y][x];
      cmax(d1[y][x + 1], d - 1);
      cmax(d1[y + 1][x], d - 1);
      cmax(d1[y + 1][x + 1], d - 1);
    }
    if (d2[y][x]) {
      paint(x - 1, y, 0), paint(x - 1, y, 1); 
      paint(x - 1, y + 1, 0), paint(x - 1, y + 1, 3);
      paint(x, y + 1, 2), paint(x, y + 1, 3);
      paint(x, y, 1), paint(x, y, 2);
      int d = d2[y][x];
      cmax(d2[y + 1][x - 1], d - 2);
      cmax(d2[y + 1][x + 1], d - 2);
      cmax(d2[y + 2][x], d - 2);
    }
  }
  cout << fixed << setprecision(2) << cnt * 0.25;
  
  
	return 0;
}


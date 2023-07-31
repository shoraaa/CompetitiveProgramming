#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e3 + 5;
int a[N][N];
queue<int> x, y;
bool vis[N][N];
int n;
int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
#define getchar_unlocked getchar
inline void readInt(int& p) {
  static char c;
  while ((c = getchar_unlocked()) < '0'); // just to be safe
  for (p = c-'0'; (c = getchar_unlocked()) >= '0'; p = p*10+c-'0');
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  readInt(n); char c; 
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      c = getchar_unlocked(); 
      if (c < '0') c = getchar_unlocked(); 
      a[i][j] = c - '0';
      if (!a[i][j]) vis[i][j] = 1, x.emplace(i), y.emplace(j);
      else a[i][j] = 1e9;
    }
    
  }
  while (!x.empty()) {
    int i = x.front(), j = y.front(); x.pop(); y.pop();
    for (int d = 0; d < 4; ++d) {
      int r = i + dr[d], c = j + dc[d];
      if (!vis[r][c]) vis[r][c] = 1;
      else if (a[i][j] + 1 < a[r][c])
        a[r][c] = a[i][j] + 1, 
        x.emplace(r), y.emplace(c);
    } 
    if (x.empty())
      cout << a[i][j];
  }
	return 0;
}


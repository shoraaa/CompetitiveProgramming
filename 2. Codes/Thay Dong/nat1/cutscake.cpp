#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2005;
int n, m;
int a[N][N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; int res = 0, last_i = -1;
  for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
    cin >> a[i][j], res += a[i][j] == 1;
    if (a[i][j]) last_i = i;
  }
  cout << res << '\n';
  int x = 1;
  for (int i = 1; i <= n; ++i) {
    int cur = 0; int last = -1;
    for (int j = 1; j <= m; ++j) {
      cur += a[i][j];
      if (a[i][j]) last = j;
    }
    if (!cur) continue;
    
    if (i == last_i) {
      for (int j = 1, y = 1; j <= m; ++j) if (a[i][j]) {
        if (j == last) cout << x << ' ' << y << ' ' << n << ' ' << m << '\n';
        else cout << x << ' ' << y << ' ' << n << ' ' << j << '\n';
        y = j + 1;
      }
      break;
    }
    
    
    for (int j = 1, y = 1; j <= m; ++j) if (a[i][j]) {
      if (j == last) cout << x << ' ' << y << ' ' << i << ' ' << m << '\n';
      else cout << x << ' ' << y << ' ' << i << ' ' << j << '\n';
      y = j + 1;
    }
    x = i + 1;
  }
	return 0;
}


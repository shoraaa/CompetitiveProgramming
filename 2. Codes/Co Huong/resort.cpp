#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "resort";
	if (!fopen((FILE_NAME + ".inp").c_str(), "r")) return;
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 1e3 + 5;
int a[N][N], s[N][N], e[N][N];
int n, m, p, q, b;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0); file();
  cin >> n >> m >> p >> q >> b;
  for (int i = 1, x; i <= n; ++i) for (int j = 1; j <= m; ++j) {
    cin >> x;
    s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + (x < b);
    e[i][j] = e[i-1][j] + e[i][j-1] - e[i-1][j-1] + (x == b);
  } 
  int res = 0, c = (p * q - 1) / 2;
  for (int i = p; i <= n; ++i) for (int j = q; j <= m; ++j) {
    int smaller = s[i][j] - s[i-p][j] - s[i][j-q] + s[i-p][j-q],
        equal = e[i][j] - e[i-p][j] - e[i][j-q] + e[i-p][j-q];
    if (smaller <= c && smaller + equal > c) res++;
  }
  cout << res;
	return 0;
}


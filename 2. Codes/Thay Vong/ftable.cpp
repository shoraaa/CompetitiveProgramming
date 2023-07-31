#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "ftable";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
const int N = 500 + 5, inf = 2e9, M = 2e6;
int a[N][N];
int n, m;
int pos(int i, int j) {
  return a[i][j] > 0;
}
int neg(int i, int j) {
  return a[i][j] < 0;
}
int di[4] = {0, 0, 1, 1}, dj[4] = {0, 1, 0, 1};
void calc(int i, int j) {
  vector<int> v = {a[i][j], a[i+1][j], a[i][j+1], a[i+1][j+1]};
  sort(v.begin(), v.end());
  int m = v[1];
  a[i][j] -= m, a[i+1][j] -= m, a[i][j+1] -= m, a[i+1][j+1] -= m;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0); //file();
  cin >> n >> m;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    cin >> a[i][j];
  for (int k = 0; k < M / (n * m); ++k) 
    for (int i = 0; i < n-1; ++i) 
      for (int j = 0; j < m-1; ++j) 
        calc(i, j);
  for (int k = 0; k < M / (n * m); ++k) 
    for (int i = n-2; ~i; --i) 
      for (int j = m-2; ~j; --j) 
        calc(i, j);
  ll res = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
    res += abs(a[i][j]);
  cout << res;
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2000 + 5, inf = 1e9;
int n, m, max_val = -inf, min_val = inf;
void flipRow(vector<vector<int>>& a) {
  for (int i = 0; i < n/2; ++i)
    for (int j = 0; j < m; ++j) swap(a[i][j], a[n-i-1][j]);
}
void flipCol(vector<vector<int>>& a) {
  for (int j = 0; j < m/2; ++j) 
    for (int i = 0; i < n; ++i) swap(a[i][j], a[i][m-j-1]);
}
int top(int mid, vector<vector<int>>& a) {
  for (int i = 0, cur_r = m-1; i < n; ++i) {
     for (int j = cur_r; ~j; --j) if (max_val - a[i][j] > mid) cur_r = j-1;
     for (int j = cur_r+1; j < m; ++j) if (a[i][j] - min_val > mid) return 0;
  }
  return 1;
}
vector<vector<int>> a[4];
int check(int mid) {
  for (int i = 0; i < 4; ++i)
    if (top(mid, a[i])) return 1;
  return 0; 
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; a[0].resize(n, vector<int>(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> a[0][i][j], 
      max_val = max(max_val, a[0][i][j]),
      min_val = min(min_val, a[0][i][j]);
  a[3] = a[2] = a[1] = a[0];
  for (int i = 0; i < 4; ++i) {
    if (i & 1) flipRow(a[i]);
    if (i & 2) flipCol(a[i]);
  }
  int lo = 0, hi = max_val - min_val, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid))
      ans = mid, hi = mid - 1;
    else
      lo = mid + 1;
  }
  cout << ans << '\n';
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
int a[N], delta[N], sum[N], val[N], comp[N], red[N];
int n, rc, m, k, c = 0;
int inside(int r, int c) {
  return 0 <= r && r < rc && 0 <= c && c < m;
}
int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
void dfs(int r, int c, int cid) {
  int i = r * m + c;
  comp[i] = cid, sum[cid] += a[i];
  if (red[i]) delta[cid] -= 3;
  else delta[cid] += 1, val[cid] = min(val[cid], a[i]);;
  for (int d = 0; d < 4; ++d) if (inside(r + dr[d], c + dc[d])) {
    int j = (r + dr[d]) * m + c + dc[d];
    if (comp[j]) continue; // visited
    if (red[i] || red[j])
      dfs(r + dr[d], c + dc[d], cid);
  }
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m, rc = n, n *= m;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  cin >> k;
  for (int i = 0, r, c; i < k; ++i)
    cin >> r >> c, 
    red[r * m + c] = 1;
  memset(val, 0x3f, sizeof(val));
  for (int i = 0; i < n; ++i) 
    if (!comp[i] && red[i])
      c++, dfs(i / m, i % m, c);
  int res = 0;
  for (int i = 1; i <= c; ++i) {
    if (delta[i] < 0)
      return cout << "No", 0;
    res += sum[i];
    if (delta[i] > 0) 
      res -= val[i];
  }
  cout << res;
	return 0;
}


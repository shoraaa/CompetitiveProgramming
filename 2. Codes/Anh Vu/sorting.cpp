#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
void file() {
	const string FILE_NAME = "sorting";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
vector<pair<int, int>> T, D;
int a[N], vis[N];
int n, m;
int check(int mid) {
  for (int i = 0; i <= mid; ++i)
    swap(a[T[i].first], a[T[i].second]);
  memset(vis, 0, sizeof(vis));
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (vis[i] || i == a[i]) continue;
    int csiz = 0, j = i;
    while (!vis[j]) {
      vis[j] = 1, j = a[j], csiz++;
    }
    ans += csiz - 1;
  }
  for (int i = mid; ~i; --i)
    swap(a[T[i].first], a[T[i].second]);
  return ans <= mid + 1;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	//file();
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  cin >> m;
  for (int i = 0, x, y; i < m; ++i)
    cin >> x >> y,
    T.emplace_back(x, y);
  int lo = 0, hi = m-1, mid, ans = -2;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid)) 
      ans = mid,
      hi = mid - 1;
    else
      lo = mid + 1;
  }
  cout << ans + 1;
	return 0;
}


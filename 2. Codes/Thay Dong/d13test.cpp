#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1000 + 5;
pair<int, int> a[N];
int n;
#define bit(x, k) (x & (1 << (k)))
void solve(int l, int r, int k) {
  if (l >= r) return;
  sort(a + l, a + r + 1, [&](pair<int, int>& u, pair<int, int>& v) {
    return bit(u.first, k) < bit(v.first, k);
  });
  int m = l;
  while (m <= r && bit(a[m].first, k) == 0) m++;
  if (m == l || m == r + 1) return;
  solve(l, m-1, k+1);
  solve(m, r, k+1);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
    cin >> n;
    for (int i = 0; i < n; ++i)
      cin >> a[i].first, a[i].second = i;
    solve(0, n-1, 0);
    for (int i = 0; i < n; ++i)
      cout << a[i].second + 1 << ' ';
    cout << '\n';
  }
	return 0;
}
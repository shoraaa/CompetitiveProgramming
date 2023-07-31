#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
ll x[N], y[N]; int n;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("hangrao.inp", "r"))
    freopen("hangrao.inp", "r", stdin),
    freopen("hangrao.out", "w", stdout);
  int T;
  cin >> T;
  while (T--) {
    cin >> n; multiset<int> sx, sy;
    for (int i = 0; i < n; ++i)
      cin >> x[i] >> y[i],
      sx.insert(x[i]),
      sy.insert(y[i]);
    if (n == 1) {
      cout << 0 << '\n';
      continue;
    }
    ll res = 1e18;
    for (int i = 0; i < n; ++i) {
      sx.erase(sx.find(x[i])), sy.erase(sy.find(y[i]));
      ll min_x = *sx.begin() - 1, max_x = *sx.rbegin() + 1;
      ll min_y = *sy.begin() - 1, max_y = *sy.rbegin() + 1;
      res = min(res, max_x - min_x + max_y - min_y);
      sx.insert(x[i]), sy.insert(y[i]);
    }
    cout << res * 2 << '\n';
  }
	return 0;
}


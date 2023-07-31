#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 100 + 5;
int a[N], del[N];
pair<int, int> b[N];
int n, m;
int check(int l, int r) {
  for (int i = 0; i < n; ++i) del[i] = 0;
  for (int i = l; i <= r; ++i) del[i] = 1;
  for (int i = 0; i < m; ++i) {
    int l = b[i].first, r = b[i].second;
    map<int, bool> mp;
    for (int j = l; j <= r; ++j) if (!del[j]) {
      if (mp.count(a[j])) 
        return 0;
      mp[a[j]] = 1;
    }
  }
  return 1;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
      cin >> a[i];
    for (int i = 0; i < m; ++i)
      cin >> b[i].first >> b[i].second, b[i].first--, b[i].second--;
    if (check(n, n)) {
      cout << 0 << '\n'; continue;
    }
    int res = n;
    for (int i = 0; i < n; ++i) for (int j = i; j < n; ++j) if (check(i, j)) { 
      res = min(res, j - i + 1); break; 
    }
    cout << res << '\n';
  }
	return 0;
}


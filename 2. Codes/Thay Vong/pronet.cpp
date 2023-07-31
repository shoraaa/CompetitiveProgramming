#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;
int a[N], b[N], vis[N];
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("pronet.inp", "r"))
    freopen("pronet.inp", "r", stdin),
    freopen("pronet.out", "w", stdout);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i] >> b[i];
  vector<int> c(n), d(n);
  iota(c.begin(), c.end(), 0);
  iota(d.begin(), d.end(), 0);
  sort(c.begin(), c.end(), [&](int i, int j) {
    return a[i] < a[j];
  });
  sort(d.begin(), d.end(), [&](int i, int j) {
    return b[i] < b[j];
  });
  for (int i : c) cerr << a[i] << '\n';
  ll res = 0; int cnt = 0;
  for (int i = 0, j = 0; cnt < n;) {
    while (i < n && (vis[c[i]] || a[c[i]] <= cnt)) {
      if (!vis[c[i]]) vis[c[i]] = 1, cnt++;
      i++;
    }
    if (cnt == n) break;
    
    while (j < n && vis[d[j]]) j++;
    res += b[d[j]];
    vis[d[j]] = 1, cnt++;
    j++;
  }

  cout << res;
	return 0;
}


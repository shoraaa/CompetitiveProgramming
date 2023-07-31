#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5, inf = 1e9;
int a[N], b[N], c[N * 2];
vector<int> pos[N * 2];
int n;
int vis[N], spt[N][20], bit[N];
int bit_get(int i) {
  int res = 0;
  for (; i; i -= i & -i)
    res = max(res, bit[i]);
  return res;
}
void update(int i, int x) {
  for (; i <= n; i += i & -i)
    bit[i] = max(bit[i], x);
}
int get(int l, int r) {
  if (l > r) swap(l, r);
  int k = __lg(r - l + 1);
  return max(spt[l][k], spt[r - (1 << k) + 1][k]);
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("gianlan.inp", "r"))
    freopen("gianlan.inp", "r", stdin),
    freopen("gianlan.out", "w", stdout);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i], c[i] = a[i];
  for (int i = 0; i < n; ++i)  
    cin >> b[i], c[i + n] = b[i];
  sort(c, c + n * 2);
  int m = unique(c, c + n * 2) - c;
  for (int i = n-1; ~i; --i)
    a[i] = lower_bound(c, c + m, a[i]) - c + 1,
    b[i] = lower_bound(c, c + m, b[i]) - c + 1,
    pos[a[i]].emplace_back(i), spt[i][0] = a[i];
  for (int k = 1; k < 20; ++k) 
    for (int i = 0; i + (1 << k) - 1 < n; ++i)
      spt[i][k] = max(spt[i][k-1], spt[i + (1 << (k - 1))][k-1]);
  vector<int> v; v.reserve(n); 
  for (int i = 0; i < n; ++i) if (a[i] <= b[i]) 
    for (int p : pos[b[i]]) if (get(i, p) == b[i]) v.emplace_back(p);
  int res = 0;
  for (int p : v) {
    int cur = bit_get(p) + 1;
    res = max(res, cur), update(p, cur);
  }
  cout << res;
	return 0;
}


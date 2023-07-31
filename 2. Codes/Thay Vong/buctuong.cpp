#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5;
int a[N], b[N], x[N];
ll fa[N], fb[N];
int n, m;

int bit[N];
void update(int i, int x) {
  for (; i; i -= i & -i)
    bit[i] = max(bit[i], x);
}
int get(int i) {
  int res = 0;
  for (; i <= m; i += i & -i)
    res = max(res, bit[i]);
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("buctuong.inp", "r"))
    freopen("buctuong.inp", "r", stdin),
    freopen("buctuong.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> x[i] >> a[i] >> b[i],
    fa[i] = fa[i-1] + a[i],
    fb[i] = fb[i-1] + b[i];
  vector<int> c;
  for (int i = 1; i <= n; ++i)
    c.emplace_back(fb[i] - x[i]),
    c.emplace_back(fb[i-1] - x[i]);
  sort(c.begin(), c.end()); c.erase(unique(c.begin(), c.end()), c.end());
  m = c.size(); ll res = 0;
  for (int i = n; ~i; --i) {
    update(lower_bound(c.begin(), c.end(), fb[i] - x[i]) - c.begin() + 1, i);
    int j = get(lower_bound(c.begin(), c.end(), fb[i-1] - x[i]) - c.begin() + 1);
    res = max(res, fa[j] - fa[i-1]);
  }
  cout << res;
	return 0;
}


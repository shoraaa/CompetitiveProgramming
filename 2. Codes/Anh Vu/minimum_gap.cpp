#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define fi first
#define se second
const int N = 2e5 + 5;
pair<int, int> a[N];
ll bit[N], ans[N], sum[N];
int lef[N], rig[N], v[N];
int n, m;
void update(int i, int x) {
  i++;
  for (; i <= n; i += i & -i)
    bit[i] += x;
}
ll get(int i) {
  ll res = 0;
  for (; i; i -= i & -i)
    res += bit[i];
  return res;
}
ll get(int l, int r) {
  return get(r) - get(l - 1);
}
stack<int> q[N];
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    cin >> a[i].fi, a[i].se = i;
  sort(a, a + n);
  for (int i = 0; i < n; ++i)
    v[i] = a[i].fi;
  for (int i = 0; i < m; ++i)
    cin >> lef[i] >> rig[i];
  for (int i = 0; i < m; ++i)
    q[upper_bound(v, v + n, 1) - v].emplace(i);  
  for (int i = 0; i <= n; ++i) {
    while (!q[i].empty()) {
      auto idx = q[i].top(); q[i].pop();
      ll val = get(lef[idx], rig[idx]);
      if (sum[idx] == val) ans[idx] = sum[idx] + 1;
      else sum[idx] = val, q[upper_bound(v + i, v + n, val + 1) - v].emplace(idx);  
    }
    if (i == n) break;
    update(a[i].se, a[i].fi);
  }
  for (int i = 0; i < m; ++i)
    cout << ans[i] << '\n';
	return 0;
}


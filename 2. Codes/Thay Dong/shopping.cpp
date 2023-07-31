#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define fi first
#define se second
#define int ll
const int N = 1e5 + 5;
int a[N];
pair<ll, ll> c[N];
ll sum[N], cnt[N];
int n, m, k = 0;
signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("shopping.inp", "r")) 
    freopen("shopping.inp", "r", stdin),
    freopen("shopping.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) 
    cin >> a[i];
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n;) {
    int j = i;
    while (j <= n && a[j] == a[i]) j++;
    c[++k] = {a[i], j - i}; i = j;
  }
  ll res = 0;
  for (int i = 1; i <= k; ++i) {
    res += (k - i) * c[i].se * c[i].fi; m -= k - i;
    cnt[i] = cnt[i-1] + c[i].se;
    sum[i] += sum[i-1] + c[i].fi * c[i].se;
  }
  for (int i = k; i; --i) {
    int val = m / cnt[i];
    m -= val * cnt[i], res += val * sum[i]; 
  }
  cout << res;
	return 0;
}


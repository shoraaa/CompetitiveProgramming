#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int n; ll k;
ll a[10];
ll mask[1 << 10];

int check(ll x) {
  // danh so >= k -> co >= k so ko bi xoa <= no
  ll res = 0; 
  for (int msk = 0; msk < 1 << n; ++msk) {
    ll val = x / mask[msk];
    if (__builtin_popcount(msk) & 1) res -= val;
    else res += val;
  }
  return res >= k;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  
  while (T--) {
    cin >> n >> k; 
    
    for (int i = 0; i < n; ++i) 
      cin >> a[i];

    for (int msk = 0; msk < 1 << n; ++msk) {
      mask[msk] = 1;
      for (int i = 0; i < n; ++i) 
        if (msk >> i & 1) mask[msk] = (mask[msk] * a[i]) / __gcd(mask[msk], a[i]);
    }

    ll lo = 0, hi = 1e18, mid, ans = -1;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (check(mid))
        ans = mid, hi = mid - 1;
      else
        lo = mid + 1;
    }
    cout << ans << '\n';
  }
	return 0;
}


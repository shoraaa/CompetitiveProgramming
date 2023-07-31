#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll n; int m;
ll a, b;
ll mask[1 << 20];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m; vector<ll> pr;
  // dem so ngto cung nhau voi n trong khoang [a, b]
  for (ll d = 2; d * d <= n; ++d) if (n % d == 0) {
    pr.emplace_back(d);
    while (n % d == 0) n /= d;
  }
  if (n > 1) pr.emplace_back(n);

  // dem so ko phai la boi cua it nhat 1 trong cac so trong pr trong khoang a, b
  
  for (int msk = 0; msk < 1 << int(pr.size()); ++msk) {
      mask[msk] = 1;
      for (int i = 0; i < pr.size(); ++i) 
        if (msk >> i & 1) mask[msk] *= pr[i];
  }
  
  while (m--) {
    ll res = 0; cin >> a >> b;
    for (int msk = 0; msk < 1 << int(pr.size()); ++msk) {
      ll x = mask[msk];
      ll val = b / x - (a - 1) / x;
      if (__builtin_popcount(msk) & 1) res -= val;
      else res += val;
    }
    cout << res << '\n';
  }
	return 0;
}


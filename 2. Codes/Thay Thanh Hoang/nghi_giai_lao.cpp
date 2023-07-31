#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int n;
ll a[N], f[N];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  sort(a + 1, a + n + 1, greater<ll>());
  for (int i = 1; i <= n; ++i)
    f[i] = f[i - 1] + a[i];
  ll res = 1e18;
  for (int L = 1; L <= n; ++L) {
    ll cur = 0;
    for (int i = 1, k = 0; i <= n; i += L, ++k) {
      if (k == 12) { cur = 1e18; break; }
      cur += (f[min(i + L - 1, n)] - f[i - 1]) * (1LL << k);
    }
    res = min(res, cur + 3600 * (L - 1));
  }
  cout << res;
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int a[N];
int n; ll k;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("nhanpham.inp", "r"))
    freopen("nhanpham.inp", "r", stdin),
    freopen("nhanpham.out", "w", stdout);
  cin >> n >> k; ll sum = 0;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], sum += a[i];
  
  ll cur = 0;
  for (int i = 1; i <= n; ++i) {
    cur += i - a[i];
    if (cur >= k) return cout << i, 0;
  }

  ll lo = 1, hi = ll(3e9) / n, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    ll y = 1LL * mid * n;
    if (y*(y+1)/2 >= k + mid*sum) ans = mid, hi = mid - 1;
    else lo = mid + 1;
  }
  
  if (ans == -1) 
    return cout << -1, 0;
  ans--; ll y = ans * n;
  cur = y*(y+1)/2 - ans*sum;
  for (int i = 1; i <= n; ++i) {
    cur += (ans * n + i) - a[i];
    if (cur >= k) return cout << ans * n + i, 0;
  }
  
	return 0;
}
 
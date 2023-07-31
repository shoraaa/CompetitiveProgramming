#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int a[N];
int n, k; ll l;
int check(ll val) {
  // so luong so nho thu k cua day do dai >= k ma <= val la >= l  
  ll s = 0, cnt = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    while (j < n && s < k) s += a[j] <= val, j++;
    if (s >= k) cnt += n - j + 1;
    s -= a[i] <= val;
  }
  return cnt >= l;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k >> l; 
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  int lo = 1, hi = n, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid))
      ans = mid, hi = mid - 1;
    else
      lo = mid + 1; 
  }
  cout << ans << '\n';
	return 0;
}


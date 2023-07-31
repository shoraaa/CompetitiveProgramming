#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
 
const int N = 1e5 + 5;
ld a[N], b[N];
int n;
 
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i] >> b[i];
  sort(a + 1, a + n + 1, greater<ld>());
  sort(b + 1, b + n + 1, greater<ld>());
  for (int i = 1; i <= n; ++i)
    a[i] += a[i - 1], b[i] += b[i - 1];
  ld res = 0.0;
  for (int i = 1, j = 1; i <= n; ++i) {
    while (j <= n && b[j] < a[i]) j++;
    if (j <= n) res = max(res, a[i] - i - j);
  }
  for (int i = 1, j = 1; i <= n; ++i) {
    while (j <= n && a[j] < b[i]) j++;
    if (j <= n) res = max(res, b[i] - i - j);
  }
  cout << fixed << setprecision(4) << res;
	return 0;
}
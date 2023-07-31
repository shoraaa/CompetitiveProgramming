#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
const int N = 1e6 + 5, M = 1e9 + 7;
void add(int& x, int y) {
  x += y; 
  if (x < 0) x += M;
  if (x >= M) x -= M;
}
int mul(ll x, ll y) {
  return x * y % M;
}
int sum(int l, int r) {
  if (l > r) return 0;
  return mul(r - l + 1, l + (r - l) / 2);
}
int _cnt[N * 2], fac[N], c[N];
#define cnt(x) _cnt[x + N]
int n;
signed main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; int C = 1;
  for (int i = 0, c; i < n; ++i) 
    cin >> c, C = max(C, c),
    cnt(1 - c)++,
    cnt(c + 1)--;
  fac[0] = 1;
  for (int i = 1; i <= n; ++i)
    fac[i] = mul(fac[i-1], i);
  int p = 1, res = 0, num = 1;
  for (int i = 1 - C; i <= C - 1; ++i) 
    cnt(i) += cnt(i - 2),
    add(res, mul(i, sum(p, p + cnt(i) - 1))),
    num = mul(num, fac[cnt(i)]), p += cnt(i);
  cout << res << ' ' << num;
	return 0;
}


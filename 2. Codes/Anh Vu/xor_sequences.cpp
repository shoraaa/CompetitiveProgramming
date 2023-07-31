#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 20, M = 1e9 + 7;
int mul(ll x, ll y) {
  return x * y % M;
}
int m, n;
int a[1 << N], pos[1 << N];
int call(int bit, int l) {
  if (bit == 0)
    return 1;
  int r = l + (1 << bit) - 1;
  int m = l + (1 << (bit - 1)) - 1;
  for (int i = l; i <= r; ++i)
    pos[a[i]] = -1;
  int flag = 0;
  for (int i = l; i <= m; ++i)
    pos[a[i]] = i;
  for (int i = m+1; i <= r; ++i)
    if (pos[a[i]] != -1) flag = 1;
  if (!flag) return mul(call(bit - 1, l), call(bit - 1, m+1));
  for (int i = m+1; i <= r; ++i)
    if (a[i - (1 << (bit - 1))] != a[i]) return 0;
  return mul(call(bit - 1, l), 2);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> m >> n;
  for (int i = 0; i < 1 << m; ++i)
    cin >> a[i];
  cout << call(m, 0);
	return 0;
}


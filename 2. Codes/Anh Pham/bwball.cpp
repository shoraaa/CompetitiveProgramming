#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
using ii = pair<int, int>;
int n, m;
ii operator += (ii& a, ii b) {
  ii c;
  c.first = a.first * b.second + b.first * a.second;
  c.second = a.second * b.second;
  int g = __gcd(c.first, c.second);
  c.first /= g, c.second /= g;
  if (c.second < 0) c.second = -c.second, c.first = -c.first;
  a = c; return c;
}
ii operator *= (ii& a, ii b) {
  ii c;
  c.first = a.first * b.first, c.second = a.second * b.second;
  int g = __gcd(c.first, c.second);
  c.first /= g, c.second /= g;
  if (c.second < 0) c.second = -c.second, c.first = -c.first;
  a = c; return c;
}
signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> m >> n;             
  ii res = {0, 1};
  for (int i = 1; i <= m + 1; ++i) {
    ii cur = {5 * i * n, n + m - i + 1};
    if (i & 1) cur *= ii(-1, 1);
    for (int j = 1; j < i; ++j)
      cur *= ii(m - j + 1, n + m - j + 1);
    res += cur;
  }
  cout << res.first << '/' << res.second; 
	return 0;
}


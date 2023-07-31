#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
int p[N], z[N];
ll c[N];
string s, t;
int n, m;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> s >> t; n = s.size(), m = t.size();
  t = ' ' + t, s = t + ' ' + s;
  ll res = ll(n) * m;
  int l = 0, r = 0;
  for (int i = 2; i <= m+n+1; ++i) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l + 1]);
    else 
      z[i] = 0;
    while (i + z[i] <= m+n+1 && s[z[i] + 1] == s[i + z[i]])
      ++z[i], l = i, r = i + z[i] - 1;
    if (i > m+2) c[1]++, c[z[i] + 1]--; 
  }
  for (int i = 1; i <= m; ++i)
    c[i] += c[i-1];
  p[1] = 0;
  for (int i = 2; i <= m; ++i) {
    int k = p[i-1];
    while (k > 0 && t[k + 1] != t[i])
      k = p[k];
    if (t[k + 1] == t[i])
      p[i] = k + 1,
      res -= c[i - p[i]];
    else
      p[i] = 0;
  }
  cout << res;
	return 0;
}


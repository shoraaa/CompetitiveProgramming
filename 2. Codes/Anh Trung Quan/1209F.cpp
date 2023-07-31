#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;

using Tp = unsigned long long;
Tp pw[N], base = 31;
struct Hash {
  vector<Tp> pre, suf;
  int n;
  Hash(string s): n(s.size()), pre(s.size() + 1), suf(s.size() + 1) {
    for (int i = 1; i <= n; ++i)
      pre[i] = pre[i-1] * base + s[i-1] - 'a' + 1;
    for (int i = n; i; --i)
      suf[i] = suf[i+1] * base + s[i-1] - 'a' + 1;
  }
  Tp get(int l, int r) {
    if (l == 0 || r == 0 || l == n + 1 || r == n + 1) return 0;
    if (l <= r) 
      return pre[r] - pre[l-1] * pw[r - l + 1];
    else
      return suf[r] - suf[l+1] * pw[l - r + 1];
  }
  int rev(int l, int r) {
    Tp prefix = get(1, l-1) * pw[n - l + 1] + get(r, l) * pw[n - r] + get(r + 1, n);
    Tp suffix = get(n, r + 1) * pw[r] + get(l, r) * pw[l - 1] + get(l - 1, 1);
    return prefix == suffix;
  }
  
};

int pl[N];
int n; string t;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> t, n = t.size();
  pw[0] = 1;
  for (int i = 1; i <= n; ++i)
    pw[i] = pw[i-1] * base;
  int p = 0;
  while (p * 2 < n && t[p] == t[n-p-1]) p++;
  if (p * 2 >= n)
    return cout << 1 << ' ' << 1, 0;
  Hash s(t.substr(p, n-2*p)); n = s.n;
  for (int i = 1; i <= n; ++i) if (s.rev(1, i))
    return cout << p + 1 << ' ' << p + i << '\n', 0;
  for (int i = n; i; --i) if (s.rev(i, n))
    return cout << p + i << ' ' << n + p << '\n', 0;
  cout << -1 << ' ' << -1;
	return 0;
}


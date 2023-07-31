#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;
string s, t; int n;
array<int, 26> cnt[N], tot;
int check(int l, int r) {
  for (int c = 0; c < 26; ++c)
    if (cnt[r][c] - cnt[l-1][c] > tot[c]) return 0;
  return 1;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> s >> t, n = s.size(); s = ' ' + s;
  for (char c : t) tot[c - 'a']++;
  ll res = 0;
  for (int i = 1; i <= n; ++i) {
    for (int c = 0; c < 26; ++c)
      cnt[i][c] = cnt[i-1][c];
    cnt[i][s[i] - 'a']++;
    int lo = 1, hi = i, mid, ans = -1;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (check(mid, i))
        ans = mid, hi = mid - 1;
      else
        lo = mid + 1;
    }
    if (ans != -1)
      res += i - ans + 1;
  }
  cout << res;
	return 0;
}


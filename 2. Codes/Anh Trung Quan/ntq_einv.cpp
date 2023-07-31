#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int a[N], c[N];
int n, m; ll k;

int bit1[N], bit2[N];
int prefix(int i) {
  int res = 0;
  for (; i; i -= i & -i)
    res += bit1[i];
  return res;
}
int suffix(int i) {
  int res = 0; if (i == 0) return 0;
  for (; i <= m; i += i & -i)
    res += bit2[i];
  return res;
}
void add(int i) {
  for (; i; i -= i & -i)
    bit2[i]++;
}
void update(int i, int x) {
  if (i == 0) return;
  for (; i <= m; i += i & -i)
    bit1[i] += x;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> a[i], c[i] = a[i];
  sort(c, c + n); m = unique(c, c + n) - c;
  for (int i = 0; i < n; ++i)
    a[i] = lower_bound(c, c + m, a[i]) - c + 1;
  ll cur = 0;
  int l = 0, r = n; add(a[l]);
  while (r - 1 >= 0) {
    int nxt = suffix(a[r - 1] + 1) + prefix(a[r - 1] - 1);
    if (cur + nxt > k) break; 
    update(a[r - 1], 1); cur += nxt, r--;
  }
  ll res = n - r;
  for (l++; l < n; ++l) {
    cur += prefix(a[l] - 1) + suffix(a[l] + 1), add(a[l]);
    while (r < n && (r <= l || cur > k)) 
      cur -= suffix(a[r] + 1) + prefix(a[r] - 1), update(a[r], -1), r++;
    if (cur > k) break;
    res += n - r;
  } 
  cout << res;
	return 0;
}


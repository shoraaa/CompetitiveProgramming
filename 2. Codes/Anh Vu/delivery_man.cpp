#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
int a[N], spt[N][20][2], f[N];
int n;
int check(int l, int r, int v, int p, int t =0) {
  if (l > r) return 1;
  int k = __lg(r - l + 1);
  int mx = max(spt[l][k][0], spt[r-(1<<k)+1][k][0]);
  int mn = min(spt[l][k][1], spt[r-(1<<k)+1][k][1]);
  return v-p <= mn && mx <= v+p;
}
int check(int d) {
  memset(f, 0, sizeof(f));
  f[1]++, f[2]--;
  for (int i = 1; i < n; ++i) {
    f[i] += f[i-1];
    if (f[i] > 0 && abs(a[i] - a[i-1]) <= d) {
      if (check(i+1, n-1, a[i], d) || check(i+1, n-1, a[i-1], d)) 
        return 1;
      int lo = i+1, hi = n, mid, ans = -1;
      while (lo <= hi) {
        mid = lo + hi >> 1;
        if (check(i, mid-1, a[i-1], d))
          ans = mid, lo = mid + 1;
        else
          hi = mid - 1;
      }
      if (ans != -1)
        f[i+1]++, f[ans+1]--;
    } 
  }
  return 0;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> a[0] >> a[1];
  for (int i = 0; i < n; ++i)
    cin >> a[i + 2];
  n += 2;
  for (int i = 0; i < n; ++i)
    spt[i][0][0] = spt[i][0][1] = a[i];
  for (int j = 1; j < 17; ++j)
    for (int i = 0; i + (1 << j) - 1 < n; ++i)
      spt[i][j][0] = max(spt[i][j-1][0], spt[i+(1<<(j-1))][j-1][0]),
      spt[i][j][1] = min(spt[i][j-1][1], spt[i+(1<<(j-1))][j-1][1]);
  int lo = 0, hi = 1e9, mid, ans;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid))
      ans = mid, hi = mid - 1;
    else 
      lo = mid + 1;
  }
  cout << ans;
	return 0;
}


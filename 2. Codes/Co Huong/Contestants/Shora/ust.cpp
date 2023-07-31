#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e2 + 5;
pair<int, int> a[N];
#define fi first
#define se second
int n, t;

ll x; int cnt; int flag = 0;

void call(int i = 0, int j = 0, ll val = 1) {
  if (cnt == t) return;
  if (j < a[i].se && val * a[i].fi <= x) 
    cnt++, call(i, j + 1, val * a[i].fi);
  else if (i < n-1 && val * a[i + 1].fi <= x)
    cnt++, call(i + 1, 1, val * a[i + 1].fi);
  if (cnt == t) return;
  if (i < n-1 && j > 0 && val / a[i].fi * a[i + 1].fi <= x) 
    cnt++, call(i + 1, 1, val / a[i].fi * a[i + 1].fi);
}

int check(ll mid) {
  x = mid; cnt = 1; 
  call();
  return cnt >= t;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("ust.inp", "r"))
    freopen("ust.inp", "r", stdin),
    freopen("ust.out", "w", stdout);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i].fi >> a[i].se;
  sort(a, a + n);
  for (int i = 0; i < 3; ++i) {
    cin >> t; 
    ll lo = 1, hi = 1e15, mid, ans = -1;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (check(mid))
        ans = mid, hi = mid - 1;
      else lo = mid + 1;
    }
    cout << ans << '\n';
  }
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
struct Tp {
  int dl, cnt;
  bool operator < (const Tp& t) const {
    return dl < t.dl;
  }
} a[N];
int n, m;
int check(ll s) {
  int skipped = 0;
  ll total = 0;
  priority_queue<int> q;
  for (int i = 0; i < n; ++i) {
    total += a[i].cnt;
    q.emplace(a[i].cnt);
    if (a[i].dl * s < total) 
      total -= q.top(), q.pop(),
      skipped++;
  }
  return skipped <= m;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) 
    cin >> a[i].cnt >> a[i].dl;
  sort(a, a + n);
  ll lo = 0, hi = 1e15, mid, ans = 1e15;
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


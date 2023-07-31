#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 5;
const ll INF = 2e18;
ll x[N], y[N];


int n;

int check(ll r) {
  ll left = -INF, right = INF, down = -INF, top = INF;
  for (int i = 0; i < n; ++i) {
    // (x, y + r), (x + r, y), (x, y - r), (x - r, y)
    // (x - y - r, x + y + r), 
    // (x - y + r, x + y + r), 
    // (x - y + r, x + y - r), 
    // (x - y - r, x + y - r)
    left = max(left, x[i] - y[i] - r);
    right = min(right, x[i] - y[i] + r);
    down = max(down, x[i] + y[i] - r);
    top = min(top, x[i] + y[i] + r);
    if (left > right || down > top) return 0;
  }
  return 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> x[i] >> y[i];
  ll lo = 0, hi = INF, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid)) ans = mid, hi = mid - 1;
    else lo = mid + 1;
  } 
  cout << ans;
	return 0;
}


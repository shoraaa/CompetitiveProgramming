#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e4 + 5;

pair<int, int> a[N], b[N];

#define fi first
#define se second

int n, m;

int check(int mid) {
  for (int i = 1; i <= mid; ++i) {
    b[i] = a[i];
  }
  
  sort(b + 1, b + mid + 1);
  
  set<int> s;
  for (int i = 1; i <= m; ++i) {
    s.emplace(i);
  }
  
  for (int i = 1; i <= mid; ++i) {
    
    auto it = s.lower_bound(b[i].se);
    if (it == s.end() || *it > b[i].fi) {
      return 0;
    }
    s.erase(it);
    
  }
  
  return 1;
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> m >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i].se >> a[i].fi;
    }
    
    int lo = 2, hi = n, mid, ans = 1;
    while (lo <= hi) {
      mid = (lo + hi) / 2;
      if (check(mid)) {
        ans = mid;
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }
    cout << ans << '\n';
    
  }
	return 0;
}


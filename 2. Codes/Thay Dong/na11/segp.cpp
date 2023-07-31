#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;
int a[N], spt[N][18], lef[N];
int n;

int get(int l, int r) {
  int k = __lg(r - l + 1);
  return __gcd(spt[l][k], spt[r - (1 << k) + 1][k]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i], spt[i][0] = a[i];
  for (int j = 1; j < 18; ++j) for (int i = 0; i + (1 << j) - 1 < n; ++i)
    spt[i][j] = __gcd(spt[i][j - 1], spt[i + (1 << (j - 1))][j - 1]);
  
  map<int, int> last, next;
  
  for (int i = 0, lo, hi, mid, ans; i < n; ++i) {
    lo = last.count(a[i]) ? last[a[i]] + 1 : 0, hi = i, ans = i;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (get(mid, i) == a[i]) 
        ans = mid, hi = mid - 1;
      else lo = mid + 1;
    }
    lef[i] = ans; last[a[i]] = i;
  }
  ll res = 0;
  for (int i = n - 1, lo, hi, mid, ans; ~i; --i) {
    lo = i, hi = next.count(a[i]) ? next[a[i]] - 1 : n - 1, ans = i;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (get(i, mid) == a[i]) 
        ans = mid, lo = mid + 1;
      else hi = mid - 1;
    }
    res += ll(i - lef[i] + 1) * (ans - i + 1) - 1; next[a[i]] = i;
    
  }
  cout << res;
  
	return 0;
}


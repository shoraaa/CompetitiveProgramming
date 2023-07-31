#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int a[N], spt[N][20], L[N], R[N];
int n;
int get(int l, int r) {
  int k = __lg(r - l + 1);
  return max(spt[l][k], spt[r - (1 << k) + 1][k]);
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], spt[i][0] = a[i];
  for (int k = 1; k < 18; ++k)
    for (int i = 0; i + (1 << k) - 1 < n; ++i)
      spt[i][k] = max(spt[i][k-1], spt[i + (1 << (k-1))][k-1]);
  stack<int> st; st.emplace(0);
  for (int i = 1; i <= n; ++i) {
    while (a[st.top()] > a[i]) st.pop();
    L[i] = st.top(); st.emplace(i);
  }
  st = stack<int>(); st.emplace(n+1);
  for (int i = n; i; --i) {
    while (a[st.top()] > a[i]) st.pop();
    R[i] = st.top(); st.emplace(i);
  }
  ll res = ll(n) * (n + 1) / 2;
  for (int i = 1; i <= n; ++i) {
    if (!L[i]) continue; // L[i] < a[i]
    int lo = 1, hi = L[i], mid, ans = L[i];
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (get(mid, L[i]) < a[i]) 
        ans = mid, hi = mid - 1;
      else
        lo = mid + 1;
    }
    res += ll(L[i] - ans + 1) * (R[i] - i);
  }
  cout << res;
	return 0;
}


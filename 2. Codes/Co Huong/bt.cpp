#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 52;
vector<int> arr = {(int)-1e9 - 7};
int n, a[MAX_N], dp[MAX_N][MAX_N];

int dq(int l, int r) {
   if (l >= r) return 0;
   int &cur = dp[l][r];
   if (cur != -1) return cur;
   cur = 0;
   if (a[l] == a[r]) cur = max(cur, dq(l + 1, r - 1) + 1);
   for (int i = l; i < r; i++)
      cur = max(cur, dq(l, i) + dq(i, r));
   return cur;
}

int32_t main() {
   cin.tie(0) -> sync_with_stdio(0);
   if (fopen("email.inp", "r"))
      freopen("email.inp", "r", stdin),
      freopen("email.out", "w", stdout);
   cin >> n;
   for (int i = 1; i <= n; i++)
      cin >> a[i], arr.emplace_back(a[i]);
   sort(arr.begin(), arr.end());
   arr.resize(unique(arr.begin(), arr.end()) - arr.begin());
   for (int i = 1; i <= n; i++)
      a[i] = lower_bound(arr.begin(), arr.end(), a[i]) - arr.begin();
   memset(dp, -1, sizeof dp);
   cout << n - dq(1, n);
}

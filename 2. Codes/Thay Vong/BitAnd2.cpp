#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5;

int n;
int a[N], dp[1 << 20];

void cmax(int& x, int y) { x = max(x, y); }

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("BitAnd2.inp", "r"))
    freopen("BitAnd2.inp", "r", stdin),
    freopen("BitAnd2.out", "w", stdout);
  cin >> n; int tot = (1 << 20) - 1;
  for (int i = 0; i < n; ++i)
    cin >> a[i], dp[a[i]] = a[i];
  for (int i = 0; i < 20; ++i) for (int msk = 0; msk <= tot; ++msk)
    if (msk >> i & 1) cmax(dp[msk], dp[msk ^ (1 << i)]);
  for (int i = 0; i < n; ++i)
    cout << dp[~a[i] & tot] << ' ';
	return 0;
}


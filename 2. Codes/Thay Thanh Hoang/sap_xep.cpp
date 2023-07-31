#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;

int n; 
int a[N], mx[N], dp[N], spt[N][20];

int get(int l, int r) {
  int k = __lg(r-l+1);
  return max(spt[l][k], spt[r-(1<<k)+1][k]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; mx[0] = -1e9;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i], mx[i] = max(mx[i-1], a[i]);
    if (mx[i] == i) spt[i][0] = i;
  }
  for (int j = 1; j < 20; ++j)
    for (int i = 1; i + (1 << j) - 1 <= n; ++i)
      spt[i][j] = max(spt[i][j-1], spt[i + (1 << (j-1))][j-1]);
  int S = sqrt(n);
  dp[0] = 0;
  for (int c = 0; c <= S; ++c) {
    int i = dp[c];
    while (i <= n && a[i + 1] == i + 1) i++;
    dp[c] = i;
    for (int s = 1; c + s <= S; ++s) {
      int l = min(n, i+1 + s*s - 1), r = min(n, i+1 + (s+1)*(s+1) - 2);
      dp[c + s] = max(dp[c + s], get(l, r));
    }
    if (dp[c] == n) return cout << c, 0;
  }
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 305;
const ll INF = 1e15;

int a[N];
ll dp[N][N][N / 2];
bitset<N> vis[N / 2][N];
int n, k;

ll call(int l, int r, int k) {
  if (k == 0) return 0;
  if (l >= r) return -INF;
  if (vis[k][l][r]) return dp[l][r][k];
  vis[k][l][r] = 1;
  
  ll res = 0;
  res = max(res, call(l + 2, r, k - 1) + abs(a[l] - a[l + 1]));
  res = max(res, call(l, r - 2, k - 1) + abs(a[r] - a[r - 1]));
  res = max(res, call(l + 1, r - 1, k - 1) + abs(a[l] - a[r]));
  res = max(res, call(l + 1, r, k));
  res = max(res, call(l, r - 1, k));
  
  return dp[l][r][k] = res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  
  cout << call(1, n, k);
  
	return 0;
}

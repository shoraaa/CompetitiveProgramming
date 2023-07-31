#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5, M = 1e9 + 7;
pair<int, int> spt[N][20];

#define fi first
#define se second

map<tuple<int, int, int>, int> dp;
int n, m;

int get(int l, int r) {
  int k = __lg(r - l + 1);
  return -max(spt[l][k], spt[r - (1 << k) + 1][k]).se;
}

int call(int l, int r, int k) {
  if (l > r) return 1;
  if (k == 0) return 0;
  if (dp.count(make_tuple(l, r, k))) return dp[make_tuple(l, r, k)];
  int m = get(l, r); 
  return dp[make_tuple(l, r, k)] = (call(l, r, k-1) + ll(call(l, m-1, k-1)) * call(m+1, r, k) % M) % M;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
      cin >> spt[i][0].fi, spt[i][0].se = -i;
    for (int j = 1; j < 20; ++j)
      for (int i = 0; i + (1 << j) - 1 < n; ++i)
        spt[i][j] = max(spt[i][j-1], spt[i+(1<<(j-1))][j-1]);
    cout << call(0, n-1, m) << '\n'; dp.clear();
  }

	return 0;
}


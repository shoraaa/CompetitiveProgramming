#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
int a[N], spt[N][20]; ll f[N];
int n, k;

int get(int l, int r) {
  int k = __lg(r - l + 1);
  return __gcd(spt[l][k], spt[r - (1 << k) + 1][k]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  if (fopen("photo.inp", "r"))
    freopen("photo.inp", "r", stdin),
    freopen("photo.out", "w", stdout);

  cin >> n >> k;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], f[i] = f[i - 1] + a[i], spt[i][0] = a[i];
  for (int j = 1; j < 20; ++j) for (int i = 1; i + (1 << j) - 1 <= n; ++i)
    spt[i][j] = __gcd(spt[i][j-1], spt[i+(1<<(j-1))][j-1]);
  ll res = 0;
  
  vector<int> cur;
  for (int i = 1; i <= n; ++i) {
		cur.emplace_back(i);
    vector<int> nxt;
    for (int j = 0; j < cur.size(); ++j) {
    	if (j == 0 || get(cur[j], i) != get(cur[j - 1], i)) nxt.emplace_back(cur[j]);
		 	if (i - cur[j] + 1 >= k) res = max(res, (f[i] - f[cur[j] - 1]) * get(cur[j], i));
		}
		cur.swap(nxt);
  }
  cout << res;
  return 0;
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5;
pair<int, int> spt[N][20];
#define fi first
#define se second
int n;

pair<int, int> get(int l, int r) {
  int k = __lg(r - l + 1);
  return min(spt[l][k], spt[r - (1 << k) + 1][k]);
}

int call(int l, int r, int k) {
  if (l > r) return 0;
  auto p = get(l, r);
  return call(l, p.se - 1, p.fi) + call(p.se + 1, r, p.fi) + (p.fi > k);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("poster.inp", "r"))
    freopen("poster.inp", "r", stdin),
    freopen("poster.out", "w", stdout);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> spt[i][0].fi >> spt[i][0].fi, spt[i][0].se = i;
  for (int j = 1; j < 20; ++j) for (int i = 0; i + (1 << j) - 1 < n; ++i)
    spt[i][j] = min(spt[i][j-1], spt[i+(1<<(j-1))][j-1]);
  cout << call(0, n-1, 0);
	return 0;
}


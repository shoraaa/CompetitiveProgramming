#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define bitcount(msk) (__builtin_popcount(msk))
#define bit(msk, i) ((msk) & (1 << (i)))

int cmin(ll& x, ll y) {
  return x > y ? x = y, 1 : 0;
}

const int N = 1e6 + 5;
int a[N], bad[20][20]; ll dp[1 << 20];
int n, m, k;

int eval(int x, int y){
  if (x == y) return n/2;

  int maxlen = max(x, y) - min(x, y) - 1;
  int minlen = n - maxlen - 2;

  if (maxlen == minlen) return maxlen;
  if (maxlen < minlen) swap(maxlen, minlen);

  int res = maxlen;
  int l = (maxlen - minlen) / 3;
  res = min(res, max(maxlen-l, minlen+2*l));

  l = (maxlen - 2*minlen) / 2;
  if (l > 0) res = min(res, max(maxlen-l, minlen*2+l));

  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("supman.inp", "r"))
    freopen("supman.inp", "r", stdin),
    freopen("supman.out", "w", stdout);
  cin >> n >> m >> k; m *= 2;
  for (int i = 0; i < m; ++i)
    cin >> a[i], bad[i][i] = 1;
  for (int i = 0, u, v; i < k; ++i)
    cin >> u >> v, u--, v--, bad[u][v] = bad[v][u] = 1;
  memset(dp, 0x3f, sizeof(dp));
  dp[0] = 0;
  for (int msk = 3; msk < 1 << m; ++msk) {
    if (bitcount(msk) & 1) continue;
    int i = 0;
    while (!bit(msk, i)) i++;
    for (int j = i+1; j < m; ++j) if (!bad[i][j] && bit(msk, j)) 
      cmin(dp[msk], dp[msk ^ (1 << i) ^ (1 << j)] + eval(a[i], a[j]));
  }
  cout << dp[(1 << m) - 1];
	return 0;
}


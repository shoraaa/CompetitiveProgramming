#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, SZ = 316, inf = 1e9;
pair<int, int> seg[N/SZ+1][N], a[N];
int sum[N/SZ+1], del[N];
#define fi first
#define se second
int n, k, sz, S;
int cmax(pair<int, int>& x, const pair<int, int>& y) {
  if (x.fi == y.fi && y.se < x.se) return x = y, 1;
  return y.fi > x.fi ? x = y, 1 : 0;
}

pair<int, int> get() {
  int tot = 0; pair<int, int> res = {-inf, 0};
  for (int i = 0; i < sz; ++i) {
    cmax(res, seg[i][tot % k]);
    tot += sum[i];
  }
  return res;
}

void update(int p) {
  int tot = 0, blk = p / S; 
  int L = blk * S, R = min((blk + 1) * S - 1, n-1);
  
  for (int i = L; i <= R; ++i) {
    if (del[i]) { tot++; continue; }
    seg[blk][(i - tot) % k].fi = 0;
  }
    
  del[p] = 1, sum[blk]++; tot = 0;
  
  for (int i = L; i <= R; ++i) {
    if (del[i]) { tot++; continue; }
    cmax(seg[blk][(i - tot) % k], a[i]);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k; S = sqrt(n); sz = (n - 1) / S + 1;
  for (int i = 0; i < n; ++i)
    cin >> a[i].fi, a[i].se = i,
    cmax(seg[i / S][i % k], a[i]);
  for (int t = 0; t < n; ++t) {
    auto p = get(); 
    update(p.se);
    cout << p.fi << ' '; 
  }
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
	return 0;
}


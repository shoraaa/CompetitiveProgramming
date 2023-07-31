#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 1e4 + 5;

const int M = 1e9 + 123;
int sum(int x, int y) { x += y; if (x >= M) x -= M; return x; }
int dif(int x, int y) { x -= y; if (x < 0) x += M; return x; }
int mul(ll x, ll y) { return x * y % M; }
struct Hash {
  int x; ull y;
  Hash(int x = 0): x(x), y(x) {}
  Hash(int x, ull y): x(x), y(y) {}
  Hash operator + (const Hash& h) { return {sum(x, h.x), y + h.y}; }
  Hash operator - (const Hash& h) { return {dif(x, h.x), y - h.y}; }
  Hash operator * (const Hash& h) { return {mul(x, h.x), y * h.y}; }
  bool operator == (const Hash& h) { return x == h.x && y == h.y; }
  
} base(31, 37), pw[N], h1[N], h2[N];
Hash get(int l, int r) {
  if (l > r) return h2[r] - h2[l + 1] * pw[l - r + 1];
  return h1[r] - h1[l - 1] * pw[r - l + 1];
}
int n;
int d1[N], d2[N]; 
// [i - d1[i] + 1, i + d1[i] - 1]
// [i - d2[i] + 1, i + d2[i]]
pair<int, int> spt1[N][14], spt2[N][14];
pair<int, int> get1(int l, int r) {
  int k = __lg(r - l + 1);
  return max(spt1[l][k], spt1[r-(1<<k)+1][k]);
}
pair<int, int> get2(int l, int r) {
  int k = __lg(r - l + 1);
  return max(spt2[l][k], spt2[r-(1<<k)+1][k]);
}
#define fi first
#define se second
int min_rig(int l, int len) {
  if (len & 1) {
    int hlen = (len + 1) / 2; 
    
    int lo = l+hlen-1, hi = n, mid, ans = n+1;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      auto p = get1(lo, mid);
      if (p.fi * 2 - 1 >= len)
        ans = p.se + hlen - 1, hi = mid - 1;
      else
        lo = mid + 1;
    }
    return ans;
    
    // for (int i = l + hlen - 1; i <= n; ++i) 
      // if (d1[i] * 2 - 1 >= len)
        // return i + hlen - 1;
  } else {
    int hlen = len / 2;
    
    int lo = l+hlen-1, hi = n, mid, ans = n+1;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      auto p = get2(lo, mid);
      if (p.fi * 2 >= len)
        ans = p.se + hlen, hi = mid - 1;
      else
        lo = mid + 1;
    }
    return ans;
    
    // for (int i = l + hlen - 1; i <= n; ++i) 
      // if (d2[i] * 2 >= len)
        // return i + hlen;
  }
  return n+1;
}


int dp[1 << 13], a[13]; 
int k;
int call(int msk) {
  if (msk == 0) return 0;
  if (~dp[msk]) return dp[msk];
  int res = n + 1;
  for (int i = 0; i < k; ++i) if (msk >> i & 1) {
    int pos = call(msk ^ (1 << i));
    if (pos == n + 1) continue;
    res = min(res, min_rig(pos + 1, a[i]));
  }
  return dp[msk] = res;
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("palincut.inp", "r"))
    freopen("palincut.inp", "r", stdin),
    freopen("palincut.out", "w", stdout);
  pw[0] = 1;
  for (int i = 1; i < N; ++i)
    pw[i] = pw[i-1] * base;
  string s; cin >> s;
  n = s.size(); s = ' ' + s;
  for (int i = 1; i <= n; ++i)
    h1[i] = h1[i-1] * base + (s[i] - 'a' + 1);
  for (int i = n; i; --i) 
    h2[i] = h2[i+1] * base + (s[i] - 'a' + 1);
  
  for (int i = 1, lo, hi, mid, ans; i <= n; ++i) {
    lo = 1, hi = min(i, n-i+1), ans = 1;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (get(i, i-mid+1) == get(i, i+mid-1))
        ans = mid, lo = mid + 1;
      else
        hi = mid - 1;
    }
    d1[i] = ans; 
    lo = 1, hi = min(i, n-i), ans = 0;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (get(i, i-mid+1) == get(i+1, i+mid))
        ans = mid, lo = mid + 1;
      else
        hi = mid - 1;
    }
    d2[i] = ans; 
  }
  for (int i = 1; i <= n; ++i)
    spt1[i][0] = {d1[i], i}, spt2[i][0] = {d2[i], i};
  for (int j = 1; j < 14; ++j)
    for (int i = 1; i + (1 << j) - 1 <= n; ++i)
      spt1[i][j] = max(spt1[i][j-1], spt1[i+(1<<(j-1))][j-1]),
      spt2[i][j] = max(spt2[i][j-1], spt2[i+(1<<(j-1))][j-1]);
  
  int T; cin >> T;
  while (T--) {
    cin >> k;
    for (int i = 0; i < k; ++i)
      cin >> a[i];
    memset(dp, -1, sizeof(dp));
    int res = call((1 << k) - 1);
    cout << (res <= n ? "YES\n" : "NO\n"); 
  }
	return 0;
}


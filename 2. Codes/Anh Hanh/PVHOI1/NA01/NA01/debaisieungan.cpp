#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 230, M = 998244353;

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

ll n, k, L, R;

vector<ll> a, b;
#define bit_count(x) (__builtin_popcount(x))
ll dp[1 << 15];

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("debaisieungan.inp", "r"))
    freopen("debaisieungan.inp", "r", stdin),
    freopen("debaisieungan.out", "w", stdout);
  cin >> n >> k >> L >> R;
  
  // k = 1LL*2*3*5*7*11*13*17*19*23*27*29;
  // L = k - 15, R = k + 15; n = 5;
  
  ll len = (R - L + 1) % M;
  for (ll i = 2; i * i <= k; ++i) if (k % i == 0) {
    ll val = 1;
    while (k % i == 0) k /= i, val *= i;
    a.emplace_back(val);
  }
  if (k > 1) a.emplace_back(k);
  int m = a.size();
  
  // dp[msk] = so luong cac so chia het cho it nhat 1 so trong msk
  // -> dp[msk] = Z dp[1] - Z dp[2] + Z dp[3]..
  
  for (int msk = 1; msk < 1 << m; ++msk) {
    ll val = 1;
    for (int i = 0; i < m; ++i) if (msk >> i & 1) val *= a[i];
    dp[msk] = (R / val - (L - 1) / val) % M;
  }
  
  for (int i = 0; i < m; ++i) for (int msk = 1; msk < 1 << m; ++msk) {
    if (msk >> i & 1) {
      dp[msk] -= dp[msk ^ (1 << i)];
      if (dp[msk] < 0) dp[msk] += M;
    }
  }
  
  for (int msk = 2; msk < 1 << m; ++msk) if (bit_count(msk) % 2 == 0) {
    dp[msk] = M - dp[msk];
  }
  for (int msk = 1; msk < 1 << m; ++msk) {
    dp[msk] = len - dp[msk];
    if (dp[msk] < 0) dp[msk] += M;
  }
  
  ll res = pw(len, n); 
  for (int msk = 1; msk < 1 << m; ++msk) {
    ll val = 1;
    for (int i = 0; i < m; ++i) 
      if (msk >> i & 1) val *= a[i];
    ll tmp = pw(dp[msk], n);
    if (bit_count(msk) % 2 == 0) {
      res += tmp;
      if (res >= M) res -= M;
    } else {
      res -= tmp;
      if (res < 0) res += M;
    }
  }
  cout << res;
	return 0;
}


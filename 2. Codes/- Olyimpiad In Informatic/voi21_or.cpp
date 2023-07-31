#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5, M = 1e9 + 7;
int a[N], cnt[1 << 20], dp[1 << 20];
int n, k, L, R;

ll fac[N];

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M) {
    if (k & 1) {
      res = res * x % M;
    }
  }
  return res;
}

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * pw(fac[k], M - 2) % M * pw(fac[n - k], M - 2) % M;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k >> L >> R;
  
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    cnt[a[i]]++;
  }
  
  for (int i = 0; i < 20; ++i) {
    for (int msk = 0; msk < 1 << 20; ++msk) {
      if (msk >> i & 1) {
        cnt[msk] += cnt[msk ^ (1 << i)];
      }
    }
  }
  
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % M;
  }
  
  
  for (int msk = 0; msk < 1 << 20; ++msk) {
    dp[msk] = C(cnt[msk], k);
  }
  
  for (int i = 0; i < 20; ++i) {
    for (int msk = 0; msk < 1 << 20; ++msk) {
      if (msk >> i & 1) {
        dp[msk] -= dp[msk ^ (1 << i)];
        if (dp[msk] < 0) dp[msk] += M;
      }
    }
  }
  
  int res = 0;
  for (int i = L; i <= R; ++i) {
    if (i % 3 == 0) {
      res += dp[i];
      if (res >= M) res -= M;
    }
  }
  cout << res;
  
  
	return 0;
}


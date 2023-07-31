#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5, M = 1e9 + 7;
int n;

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

int ans[N], tot[N], lp[N], fac[N], inv[N], inv2[N];

ll C(int n, int k) {
  return 1LL * fac[n] * inv[k] % M * inv[n-k] % M;
}

ll calc(int k) {
  // so cach phan n thang vao k tap sao cho ko co tap nao rong
  ll res = pw(k, tot[n]);
  for (int i = 1; i <= k; ++i) {
    ll cur = pw(k - i, tot[n]) * C(k, i) % M;
    if (i & 1) {
      res -= cur; if (res < 0) res += M;
    } else {
      res += cur; if (res >= M) res -= M;
    }
  }
  res = res * inv[k] % M;
  return res;
}


ll mul = 1; int all = 0;
int cnt[N];
inline void add(int x) {
  mul += mul * inv2[cnt[x]] % M; if (mul >= M) mul -= M;
  if (cnt[x] == 0) all++; cnt[x]++;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  for (int i = 2; i*i < N; ++i) if (!lp[i])
    for (int j = i*i; j < N; j += i) lp[j] = i;
  for (int i = 2; i < N; ++i) if (!lp[i]) lp[i] = i;
 
  fac[0] = inv[0] = 1; inv2[0] = 0;
  for (int i = 1; i < N; ++i) 
    fac[i] = 1LL * fac[i - 1] * i % M,
    inv[i] = pw(fac[i], M - 2),
    inv2[i] = pw(i, M - 2);
  
  ans[1] = mul, tot[1] = all;
  for (int i = 2; i < N; ++i) {
    int x = i;
    while (x > 1) add(lp[x]), x /= lp[x]; 
    if (x > 1) add(x);
    ans[i] = mul, tot[i] = all;
  }
  
  int T; cin >> T;
  while (T--) {
    int k; cin >> n >> k; 
    // so cach phan n thang ma co co it nhat 1 hop rong
    ll res = calc(k) + calc(k - 1); 
    if (res >= M) res -= M;
    res = res * ans[n] % M;
    cout << res << '\n'; 
  }
	return 0;
}


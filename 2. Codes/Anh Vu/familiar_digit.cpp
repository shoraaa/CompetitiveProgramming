#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int M = 1e9 + 7;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
void sub(int& x, int y) {
  x -= y; if (x < 0) x += M;
}
int mul(ll x, ll y) {
  x %= M, y %= M;
  return x * y % M;
}
int pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = mul(x, x))
    if (k & 1) res = mul(res, x);
  return res;
}
vector<int> L, R; int k;
ll dp[19][1 << 10][2];
int lmsk;
ll call(int pos, int msk, int ld, int greater, int less) {
  if (pos == L.size()) 
    return msk == 0;
  if (greater && less && ~dp[pos][msk][ld])
    return dp[pos][msk][ld];
  int l = greater ? 0 : L[pos], r = less ? 9 : R[pos];
  ll res = 0;
  for (int d = l; d <= r; ++d) {
    int nmsk = msk; if (!ld || d != 0) {
      if (nmsk >> d & 1)
        nmsk ^= 1 << d;
    }
    res += call(pos + 1, nmsk, ld & (d == 0), greater | (d > l), less | (d < r));\
  }
  if (greater && less) 
    dp[pos][msk][ld] = res;
  return res;
}
ll f(int msk) {
  // so luong cac so <= r va dung cac chu cai trong msk
  return call(0, msk, 1, 0, 0);
}
int C(ll n, int k) {
  if (n < k || n < 0 || k < 0) return 0;
  // n! / k! * (n-k)!
  int t = 1, m = 1;
  for (int i = 0; i < k; ++i) 
    t = mul(t, n-i),
    m = mul(m, i+1);
  return mul(t, pw(m, M-2));
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    ll l, r; int d;
    cin >> l >> r >> k >> d;
    L.clear(); R.clear();
    while (l) L.emplace_back(l % 10), l /= 10;
    while (r) R.emplace_back(r % 10), r /= 10;
    while (L.size() < R.size()) L.emplace_back(0);
    while (R.size() < L.size()) R.emplace_back(0);
    reverse(L.begin(), L.end());
    reverse(R.begin(), R.end());
    memset(dp, -1, sizeof(dp));
    int res = 0;
    for (int msk = 0; msk < 1 << 10; ++msk) {
      int cnt = 0;
      for (int smsk = msk;; smsk = (smsk-1)&msk) {
        if (__builtin_popcount(smsk) == d) cnt++;
        if (smsk == 0) break;
      }
      ll cur = f(msk);
      if (!cur) continue;
      if ((__builtin_popcount(msk) + d) % 2 == 0) add(res, mul(cnt, C(cur, k)));
      else sub(res, mul(cnt, C(cur, k)));
    }
    cout << res << '\n';
  }
	return 0;
}


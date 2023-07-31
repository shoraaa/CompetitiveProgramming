#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5, M = 1e9 + 7;
ll fac[N], inv[N];
ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}
ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * inv[k] % M * inv[n-k] % M;
}
vector<pair<int, int>> L[N];
int _l[N], _r[N];
int n;
int call(int l, int r) {
  if (l > r) return 1;
  auto it = lower_bound(L[l].begin(), L[l].end(), pair<int, int>(r, -1));
  if (it == L[l].end() || it->first != r) 
    return 0;
  if (l == r) 
    return 1;
  int i = it->second;
  return C(r-l+1-1, i-l) * call(l, i-1) % M * call(i+1, r) % M;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
	fac[0] = inv[0] = 1;
  for (int i = 1; i < N; ++i)
    fac[i] = fac[i-1] * i % M, 
    inv[i] = pw(fac[i], M-2);
  int T = 1;
  while (cin >> n) {
    for (int l = 0; l < n; ++l)
      L[l].clear();
    for (int i = 0; i < n; ++i) cin >> _l[i];
    for (int i = 0; i < n; ++i) cin >> _r[i];
    for (int i = 0, l, r; i < n; ++i) 
      l = _l[i], r = _r[i], l--, r--,
      L[l].emplace_back(r, i);
    for (int l = 0; l < n; ++l)
      sort(L[l].begin(), L[l].end());
    cout << "Case #" << T << ": " << call(0, n-1) << '\n'; T++;
  }
	return 0;
}


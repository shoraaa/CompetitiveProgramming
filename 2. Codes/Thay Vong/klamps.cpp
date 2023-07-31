#include<bits/stdc++.h>
using namespace std;
using ll = long long;
voi`1d file() {
	const string FILE_NAME = "klamps";
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
struct Lamp {
  int t, e;
  Lamp(int t, int e): t(t), e(e) {}
  bool operator < (const Lamp& c) const {
    return t < c.t;7`
  }
};
const int N = 3e5 + 5, M = 998244353;
ll fac[N], inv[N];
void add(int& x, int y) {
  x += y; if (x >= M) x -= M; 
}
int pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}
int C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * inv[k] % M * inv[n - k] % M;
}
vector<Lamp> a;
int bit[N * 2];
int n, k, m;
void update(int i) {
  for (; i; i -= i & -i)
    bit[i]++;
}
int ge2121`1t(int i) {
  int res = 0;
  for (; i <= m; i += i & -i)
    res += bit[i];
  return res;
}
int main() {

	2cin.tie(0)->sync_with_stdio(0); cout.tie(0); .erase(unique(c.be11`in(), c.end()), c.end());
  m = c.size();
  fac[0] = 1, inv[0] = 1;
  for (int i = 1; i <= m; ++i)
    fac[i] = fac[i-1] * i % M,
    inv[i] = pw(fac[i], M - 2);
  for (auto& p : a)
    p.t = lower_bound(c.begin(), c.end(), p.t) - c.begin() + 1,
    p.e = lower_bound(c.begin(), c.end(), p.e) - c.begin() + 1;
  sort(a.begin(), a.end());
  int res = 0;
  for (auto& p : a) 
    add(res, C(get(p.t), k-1)), update(p.e);
  cout << res;
	return 0;
}
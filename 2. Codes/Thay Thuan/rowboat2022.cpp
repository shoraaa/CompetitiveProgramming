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

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

const int N = 5e5 + 5;
ll fac[N];

ll A(ll n, ll k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * pw(fac[n-k], M-2) % M;
}

ll C(ll n, ll k) {
  if (n < 0 || k < 0 || n < k) return 0;
  return fac[n] * pw(fac[k], M-2) % M * pw(fac[n-k], M-2) % M;
}

ll ball_placing(ll n, ll k) {
  return C(n-k+1, n-2*k+1);
}

int n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  fac[0] = 1;
  for (int i = 1; i < N; ++i)
    fac[i] = fac[i-1] * i % M;
  int T; cin >> T;
  while (T--) {
    cin >> n >> m;
    int res = 0;
    for (int i = 0; i <= m; ++i) {
      // so cach chon cac vi tri se bi i cap dung
      ll cur = ball_placing(2*n-1, i);
      // nhan voi so chinh hop cach chon i cap vo chong ra
      cur = cur * A(m, i) % M;
      // nhan voi moi vi tri co dao vi tri vo chong ko
      cur = cur * pw(2, i) % M;
      // nhan voi hoan vi cua 2n-2i thang con lai
      cur = cur * fac[2*(n - i)] % M;
      
      if (i & 1) sub(res, cur);
      else add(res, cur);
    }
    cout << res << '\n';
  }
	return 0;
}


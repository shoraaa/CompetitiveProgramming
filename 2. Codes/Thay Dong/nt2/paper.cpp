#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9 + 7;
void add(ll& x, int y) {
  x += y; if (x >= M) x -= M;
}
void sub(ll& x, int y) {
  x -= y; if (x < 0) x += M;
}

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

const int N = 1005;
ll row[N], col[N], pwi[N];

ll n, m, c, k;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> c >> n >> m >> k;
    
    for (int i = 1; i <= n; ++i) row[i] = 0;
    for (int i = 1; i <= m; ++i) col[i] = 0;
    
    pwi[0] = 0;
    for (int i = 1; i <= max(n, m); ++i) 
      pwi[i] = pw(i, c);
    
    for (int i = 1; i <= n; ++i) for (int j = i; j <= n; ++j) {
      ll a = i, b = n - j + 1;
      ll tmp = pwi[a] * pwi[b] % M;
      sub(tmp, pwi[a - 1] * pwi[b] % M); 
      sub(tmp, pwi[a] * pwi[b - 1] % M);
      add(tmp, pwi[a - 1] * pwi[b - 1] % M);
      
      add(row[j - i + 1], tmp);
    }
    
    for (int i = 1; i <= m; ++i) for (int j = i; j <= m; ++j) {
      ll a = i, b = m - j + 1;
      ll tmp = pwi[a] * pwi[b] % M;
      sub(tmp, pwi[a - 1] * pwi[b] % M); 
      sub(tmp, pwi[a] * pwi[b - 1] % M);
      add(tmp, pwi[a - 1] * pwi[b - 1] % M);
      
      add(col[j - i + 1], tmp);
    }
    
    ll res = 0;
    
    for (int r = 1; r <= n; ++r) for (int c = 1; c <= m; ++c) {
      if (r * c < k) continue;
      add(res, row[r] * col[c] % M);
    } 
    
    cout << res << '\n';
    
    
    
  }
	return 0;
}


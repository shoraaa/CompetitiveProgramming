#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 5, M = 998244353;

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

vector<int> divi[N];
int a[N], sum[N];
int n, m;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; m = 0;
  for (int i = 0; i < n; ++i)  
    cin >> a[i], m = max(m, a[i]);
  for (int i = 10; i <= m; ++i) divi[i].reserve(32);
  for (int i = 1; i <= m; ++i) 
    for (int j = i; j <= m; j += i) divi[j].emplace_back(i);
    
  for (int i = 0; i < n; ++i)
    for (int j : divi[a[i]]) add(sum[j], a[i]);
  for (int i = 1; i <= m; ++i)
    sum[i] = ll(sum[i]) * sum[i] % M;
  int res = 0;
  for (int i = m; i; --i) {
    add(res, pw(i, M-2) * sum[i] % M);
    for (int j : divi[i]) 
      sub(sum[j], sum[i]);
  }
  for (int i = 0; i < n; ++i)
    sub(res, a[i]);
  cout << res * pw(2, M-2) % M;
	return 0;
}


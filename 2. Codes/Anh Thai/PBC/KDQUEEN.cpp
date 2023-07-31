#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, M = 1e9 + 7;
int x[N], a[N];

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int n; cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  vector<int> c;
  int last = 2e9;
  for (int i = 0; i < n; ++i) 
    cin >> x[i],
    last = min(last, max(x[i] - 1, a[i] - x[i]));
  for (int i = 0; i < n; ++i) {
    int lim = min(last, min(x[i] - 1, a[i] - x[i]));
    if (lim) c.emplace_back(lim);
  }
  c.emplace_back(0);
  sort(c.begin(), c.end()); 
  ll res = last - c.back();
  for (int i = c.size() - 1, cur = 0; i;) {
    int j = i;
    while (~j && c[i] == c[j]) cur++, j--;
    res += (c[i] - c[j]) * pw(2, cur) % M;
    if (res >= M) res -= M; i = j;
  }
  for (int i = 0; i < n; ++i) {
    res += a[i] - 1; 
    if (res >= M) res -= M;
  }
  cout << res;
	return 0;
}


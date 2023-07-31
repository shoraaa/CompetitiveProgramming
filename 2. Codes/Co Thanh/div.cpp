#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e6 + 5;
int lp[M+1]; vector<int> pr;

using Factor = vector<pair<int, int>>;
#define fi first
#define se second

void add(Factor& a, const Factor& b) {
  Factor c;
  for (auto& p : a) c.emplace_back(p);
  for (auto& p : b) c.emplace_back(p);
  sort(c.begin(), c.end()); a = Factor();
  for (int i = 0; i < c.size();) {
    int j = i, cnt = 0;
    while (j < c.size() && c[j].fi == c[i].fi)
      cnt += c[j].se, j++;
    a.emplace_back(c[i].fi, cnt); i = j;
  }
}

Factor factor(int n) {
  Factor res;
  while (n > 1) {
    int x = lp[n], cnt = 0;
    while (n % x == 0) 
      n /= x, cnt++;
    res.emplace_back(x, cnt);
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("div.inp", "r"))
    freopen("div.inp", "r", stdin),
    freopen("div.out", "w", stdout);
  for (int i = 2; i < M; ++i) {
    if (!lp[i]) lp[i] = i, pr.emplace_back(i);
    for (int p : pr) {
      if (i * p >= M || p > lp[i]) break;
      lp[i * p] = p;
    }
  }
  int T; cin >> T;
  while (T--) {
    int m; cin >> m;
    Factor fac;
    add(fac, factor(m));
    add(fac, factor(m + 1));
    add(fac, factor(m + 2));
    
    ll res = 1; int k = fac.size();
    for (int i = 0; i < k; ++i)
      res *= fac[i].se * 2 + 1;
    res = res / 2; ll cur = 1;
    for (int i = 0; i < k; ++i)
      cur *= fac[i].se + 1;
    cur--;
    cout << res - cur << '\n';
  }


	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5, M = 1e6;
vector<int> pr; int lp[M+1], phi[M+1];
int a[N], lin[N]; ll bit[N];
int n, q, m;
int find(int i) {
  if (i == lin[i]) return i;
  return lin[i] = find(lin[i]);
}
void update(int i, int v) {
  for (; i <= n; i += i & -i)
    bit[i] += v;
}
ll get(int i) {
  ll res = 0;
  for (; i; i -= i & -i)
    res += bit[i];
  return res;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q, m = 0;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], update(i, a[i]), m = max(m, a[i]);
  phi[1] = 1;
  for (int i = 2; i <= m; ++i) {
    if (!lp[i]) lp[i] = i, pr.emplace_back(i);
    for (int p : pr) {
      if (p > lp[i] || i * p > m) break;
      lp[i * p] = p;
    }
    vector<int> fac;
    int val = i;
    while (val > 1) {
      int x = lp[val];
      fac.emplace_back(x);
      while (val % x == 0) val /= x;
    }
    int k = fac.size();
    for (int msk = 0; msk < 1 << k; ++msk) {
      int cur = 1, cnt = 0;
      for (int j = 0; j < k; ++j) if (msk >> j & 1) 
        cur *= fac[j], cnt++;
      if (cnt % 2 == 0) phi[i] += i / cur;
      else phi[i] -= i / cur;
    }
  }  /121`                                                                                                                  0-[ơ]
  for (int i = 1; i <= n+1; ++i) 
    lin[i] = i;
  for (int i = 0, t, l, r; i < q; ++i) {
    cin >> t >> l >> r;
    if (t == 1) {
      for (int j = find(l); j <= r; j = find(j+1)) {
        int v = a[j], dif = phi[v] - v;
        update(j, dif), a[j] = phi[v];
        if (a[j] == 0)
          lin[j] = j+1;
      }
    } else if (t == 2) {
      cout << get(r) - get(l-1) << '\n';
    } else {
      update(l, r - a[l]), a[l] = r, lin[l] = l;
    }
  }  
	return 0;
}


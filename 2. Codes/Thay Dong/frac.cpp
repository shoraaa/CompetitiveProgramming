#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5, M = N * 60;
ll a[N], b[M];
int h, n;

ll root = -1;
int rsz = 0;

ll get(ll p, ll q) {
  ll x = 0, y = 1, u = 1, v = 0, cp = 1, cq = 1;
  ll id = 1; int sz = 1;
  for (;;) {
    if (cp == p && cq == q) break;
    if (p * cq < cp * q) u = cp, v = cq, cp += x, cq += y, id = id * 2;
    else x = cp, y = cq, cp += u, cq += v, id = id * 2 + 1;
    sz++;
  }
  if (root == -1) root = id, rsz = sz;
  else {
    ll nroot = 0, nsz = 0;
    for (int i = 0; i < min(sz, rsz); ++i) {
      if ((root >> (rsz - i - 1) & 1) != (id >> (sz - i - 1) & 1)) break;
      nsz++;
      if (id >> (sz - i - 1) & 1) nroot = nroot * 2 + 1;
      else nroot = nroot * 2;
    }
    root = nroot; rsz = nsz;
  }
  return id;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> h >> n; h++; ll p, q;
  for (int i = 0; i < n; ++i)
    cin >> p >> q, a[i] = get(p, q);
  sort(a, a + n, greater<ll>());
  int res = 0;
  int i = 0, j = 0, m = 0;
  while (i < n || j < m) {
    ll id = max(i < n ? a[i] : 0, j < m ? b[j] : 0);
    if (id == root) break;
    while (i < n && a[i] == id) i++;
    while (j < m && b[j] == id) j++;
    b[m++] = id / 2; res++;
  }
  cout << res;
	return 0;
}


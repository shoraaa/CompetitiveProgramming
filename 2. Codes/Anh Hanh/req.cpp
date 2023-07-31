#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 4e5 + 5, Q = 1e6 + 5;
int a[N], ans[Q];

int T, n, q, m, M = 1e9 + 7;

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

struct SegmentTree {
  int n, x, y; ll res, v;
  vector<int> st;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2, 1) {}
  void update(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) return st[k] = st[k] * v % M, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    update(lc, l, m); update(rc, m+1, r);
  }
  void get(int k, int l, int r) {
    res = res * st[k] % M;
    if (l == r) return;
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    if (x <= m) get(lc, l, m);
    else get(rc, m+1, r);
  }
  void multiply(int l, int r, int v) {
    x = l, y = r, this->v = v;
    update(1, 1, n);
  }
  ll get(int x) {
    this->x = x, res = 1;
    get(1, 1, n);
    return res;
  } 
} st;

const int MX = 1e7 + 5;
int lp[MX], last[MX];

#define fi first
#define se second

signed main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("req.inp", "r"))
    freopen("req.inp", "r", stdin),
    freopen("req.out", "w", stdout);
  cin >> T >> n >> q >> M; 
  
  int m = 0;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], m = max(m, a[i]);
  
  for (int i = 2; i*i <= m; ++i) if (lp[i] == 0) 	
  	for (int j = i*i; j <= m; j += i) lp[j] = i;
	for (int i = 2; i <= m; ++i) if (!lp[i]) lp[i] = i;

	vector<tuple<int, int, int>> query; query.reserve(q);
  for (int i = 0, l, r; i < q; ++i)
    cin >> l >> r, query.emplace_back(r, l, i);
	sort(query.begin(), query.end());
	
  st = SegmentTree(n);

  for (int i = 1, j = 0, l, r, id; i <= n; ++i) {
    int x = a[i];
    while (x > 1) {
      int p = lp[x]; ll pw_p = 1;
      while (x % p == 0) x /= p, pw_p *= p;
      int lt = last[p];
      if (lt) st.multiply(1, lt, pw_p);
      st.multiply(lt + 1, i, pw_p / p * (p - 1));
      last[p] = i;
    }
    while (j < q) {
      tie(r, l, id) = query[j]; 
      if (r > i) break; j++;
      ans[id] = st.get(l);
    }
  }
  for (int i = 0; i < q; ++i)
    cout << ans[i] << ' ';
	return 0;
}


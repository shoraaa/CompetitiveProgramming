#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;

struct SegmentTree {
  int n, x, y, res;
  vector<int> st, lz;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2), lz(n * 2) {}
  void push(int k, int lc, int rc) {
    if (!lz[k]) return;
    int x = lz[k]; lz[k] = 0;
    st[lc] += x, lz[lc] += x;
    st[rc] += x, lz[rc] += x;
  }
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) return res = max(res, st[k]), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    get(lc, l, m); get(rc, m+1, r);
  }
  void update(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) return st[k]++, lz[k]++, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    update(lc, l, m); update(rc, m+1, r);
    st[k] = max(st[lc], st[rc]);
  }
  int get(int l, int r) {
    x = l, y = r, res = 0;
    get(1, 0, n - 1);
    return res;
  }
  void add(int l, int r) {
    x = l, y = r;
    update(1, 0, n - 1);
  }
} st;

pair<int, int> a[N];
#define fi first
#define se second
int c[N * 2];
int n, m, k;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> n >> k >> T;
  for (int i = 0; i < n; ++i)
    cin >> a[i].se >> a[i].fi, a[i].fi--, 
    c[i] = a[i].se, c[i + n] = a[i].fi;
  sort(c, c + n * 2); m = unique(c, c + n * 2) - c;
  sort(a, a + n);
  int res = 0; st = SegmentTree(m);
  for (int i = 0; i < n; ++i) {
    int l = lower_bound(c, c + m, a[i].se) - c, r = lower_bound(c, c + m, a[i].fi) - c;
    if (st.get(l, r) < k) res++, st.add(l, r); 
  }
  cout << res;
	return 0;
}


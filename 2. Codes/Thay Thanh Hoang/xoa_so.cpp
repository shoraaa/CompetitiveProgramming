#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5;
int n, q;
int a[N], b[N];

struct SegmentTree {
  int n, x, y, v;
  vector<int> st, lz; int res;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2), lz(n * 2) {}
  void push(int k, int lc, int rc) {
    if (!lz[k]) return;
    int x = lz[k]; lz[k] = 0;
    st[lc] += x, lz[lc] += x;
    st[rc] += x, lz[rc] += x;
  }
  void update(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) return st[k] += v, lz[k] += v, void();
    int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
    push(k, lc, rc);
    update(lc, l, m), update(rc, m+1, r);
    st[k] = max(st[lc], st[rc]);
  }
  void add(int l, int r, int v) {
    if (l > r) return;
    x = l, y = r, this->v = v;
    update(1, 1, n);
  }
} st;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; st = SegmentTree(N);
  for (int i = 0; i < n; ++i) cin >> a[i];
  for (int i = 0; i < n; ++i) cin >> b[i];
  for (int i = 0; i < n; ++i) st.add(a[i], b[i] - 1, 1);
  cout << n - st.st[1] << '\n';
  cin >> q;
  for (int i, c, d; q--;) {
    cin >> i >> c >> d; i--;
    st.add(a[i], b[i] - 1, -1);
    a[i] = c, b[i] = d;
    st.add(a[i], b[i] - 1, 1);
    cout << n - st.st[1] << '\n';
  }
	return 0;
}


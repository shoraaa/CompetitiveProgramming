#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 5;
int a[N];
int d; ll sum = 0;
struct SegmentTree {
  struct Node {
    int max; ll tag = 0;
  };
  int n, x, y, v;
  vector<Node> st;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2) {
    build(1, 0, n-1);
  }
  void build(int k, int l, int r) {
    if (l == r)
      return st[k].max = a[l], void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    build(lc, l, m), build(rc, m+1, r);
    st[k].max = max(st[lc].max, st[rc].max);
  }
  void push(int k, int lc, int rc) {
    if (st[k].tag == 0) return;
    ll tag = st[k].tag; st[k].tag = 0;
    st[lc].tag += tag, st[rc].tag += tag;
    st[lc].max += tag, st[rc].max += tag;
  }
  void update(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y)
      return st[k].max += v, st[k].tag += v, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    update(lc, l, m), update(rc, m+1, r);
    st[k].max = max(st[lc].max, st[rc].max);
  }
  void add(int l, int r, int v) {
    x = l, y = r, this->v = v;
    sum += (r - l + 1) * v;
    update(1, 0, n-1);
  }
  ll get() {
    return max((sum + d - 1) / d, ll(st[1].max)); 
  }
} st;
int n, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> d >> q;
  for (int i = 0; i < n; ++i)
    cin >> a[i], sum += a[i];
  st = SegmentTree(n);
  cout << st.get() << '\n';
  for (int i = 0, l, r; i < q; ++i)
    cin >> l >> r, l--, r--,
    st.add(l, r, -1),
    cout << st.get() + i + 1 << '\n';
	return 0;
}


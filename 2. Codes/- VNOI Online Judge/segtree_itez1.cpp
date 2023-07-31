#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
const int INF = 1e9 + 9;
int a[N];

struct SegmentTree {
  int n, x, y, v, res;
  vector<int> st;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 4) {
    build(1, 1, n);
  }
  
  void apply(int i, int v) {
    st[i] = v;
  }
  
  void pull(int i) {
    st[i] = max(st[i * 2], st[i * 2 + 1]);
  }
  
  void build(int i, int l, int r) {
    if (l == r) {
      apply(i, a[l]);
      return;
    }
    int m = (l + r) / 2;
    build(i * 2, l, m);
    build(i * 2 + 1, m + 1, r);
    pull(i);
  }
  
  void update(int i, int l, int r) {
    if (l == r) {
      apply(i, v);
      return;
    }
    int m = (l + r) / 2;
    if (x <= m) update(i * 2, l, m);
    else update(i * 2 + 1, m + 1, r);
    pull(i);
  }
  
  void get(int i, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) {
      res = max(res, st[i]);
      return;
    }
    int m = (l + r) / 2;
    get(i * 2, l, m);
    get(i * 2 + 1, m + 1, r);
  }
  
  void update(int i, int v) {
    x = i, this->v = v;
    update(1, 1, n);
  }
  
  int get(int l, int r) {
    x = l, y = r, res = -INF;
    get(1, 1, n);
    return res;
  }
  
} st;

int n, q;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  
  st = SegmentTree(n);
  cin >> q;
  for (int i = 1, t, x, y; i <= q; ++i) {
    cin >> t >> x >> y;
    if (t == 1) {
      st.update(x, y);
    } else {
      cout << st.get(x, y) << '\n';
    }
  }
  
  
	return 0;
}


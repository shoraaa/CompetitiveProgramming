#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5;

struct SegmentTree {
  int n, x, y, v; pair<int, int> res;
  vector<pair<int, int>> st;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2) {}
  void update(int k, int l, int r) {
    if (l == r)
      return st[k] = {v, l}, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    if (x <= m) update(lc, l, m);
    else update(rc, m+1, r);
    st[k] = min(st[lc], st[rc]);
  }
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y)
      return res = min(res, st[k]), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    get(lc, l, m), get(rc, m+1, r);
  }
  void update(int i, int v) {
    x = i, this->v = v;
    update(1, 0, n-1);
  }
  pair<int, int> get(int l, int r) {
    x = l, y = r, res.first = 1e9;
    get(1, 0, n-1);
    return res;
  }
} st;

vector<pair<int, int>> lef[N];
int a[N], last[N], ans[N];
int n, m, q;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n; st = SegmentTree(n);
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  cin >> q;
  for (int i = 0, l, r; i < q; ++i)
    cin >> l >> r, l--, r--,
    lef[r].emplace_back(l, i);
  memset(last, -1, sizeof(last));
  for (int i = 0; i < n; ++i) {
    if (~last[a[i]])
      st.update(last[a[i]], n);
    st.update(i, last[a[i]]);
    last[a[i]] = i;
    for (auto& p : lef[i]) {
      int l = p.first, id = p.second;
      auto res = st.get(l, i);
      if (res.first < l) 
        ans[id] = a[res.second];
    }
  }
  for (int i = 0; i < q; ++i)
    cout << ans[i] << '\n';
	return 0;
}


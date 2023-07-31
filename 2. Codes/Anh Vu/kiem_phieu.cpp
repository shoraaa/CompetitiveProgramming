#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5;
struct segment_tree {
  struct node {
    int sum, min;
  };
  int n, x, y, v;
  node res;
  vector<node> st;
  segment_tree(int n): n(n), st(2 * n - 1) {}
  void update(int k, int l, int r) {
    if (l == r) 
      return st[k].sum = st[k].min = v, void();
    int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
    if (x <= m) update(lc, l, m);
    else update(rc, m+1, r);
    st[k].sum = st[lc].sum + st[rc].sum;
    st[k].min = min(st[rc].min, st[rc].sum + st[lc].min);
  }
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return res.min = min(res.min, res.sum + st[k].min),
             res.sum += st[k].sum, void();
    int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
    get(rc, m+1, r);
    get(lc, l, m);
  }
  void update(int p, int val) {
    x = p, v = val;
    update(0, 0, n-1);
  }
  int get(int l, int r) {
    x = l, y = r, res.sum = res.min = 0;
    get(0, 0, n-1);
    return res.min;
  }
};
string s;
vector<pair<int, int>> Q[N];
int res[N];
int n, q;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> s >> q;
  for (int i = 0, l, r; i < q; ++i) 
    cin >> l >> r, l--, r--,
    Q[l].emplace_back(r, i);
  vector<int> del;
  auto get_del = [&](int r) {
    int lo = 0, hi = del.size() - 1, mid, ans = del.size();
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (del[mid] <= r)
        ans = mid,
        hi = mid - 1;
      else
        lo = mid + 1;
        
    }
    return del.size() - ans;
  };
  segment_tree st(n);
  for (int i = n-1; ~i; --i) {
    if (s[i] == 'Y') {
      del.emplace_back(i); 
    } else {
      st.update(i, 1);
      if (!del.empty())
        st.update(del.back(), -1), del.pop_back();
    }
    for (auto r : Q[i])
      res[r.second] = -st.get(i, r.first) + get_del(r.first);
  }
  for (int i = 0; i < q; ++i)
    cout << res[i] << '\n';
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5;
ll f[N];
struct segment_tree {
  struct node {
    ll val, lz;
  };
  int n, x, y, v;
  node res;
  vector<node> st;
  segment_tree(int n): n(n), st(n * 2) { build(0, 0, n-1); }
  void build(int k, int l, int r) {
    if (l == r)
      return st[k].val = f[l-1], void();
    int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
    build(lc, l, m), build(rc, m+1, r);
    st[k].val = min(st[lc].val, st[rc].val);
  }
  void update(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y)
      return st[k].val += v, st[k].lz += v, void();
    int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
    update(lc, l, m), update(rc, m+1, r);
    st[k].val = min(st[lc].val, st[rc].val) + st[k].lz;
  }
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y)
      return res.val = min(res.val, st[k].val + res.lz), void();
    int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
    res.lz += st[k].lz;
    get(lc, l, m), get(rc, m+1, r);
    res.lz -= st[k].lz;
  }
  void add(int l, int r, int val) {
    x = l, y = r, v = val;
    update(0, 0, n-1);
  }
  ll get(int l, int r) {
    x = l, y = r, res.val = 1e18, res.lz = 0;
    get(0, 0, n-1);
    return res.val;
  }
};
map<int, int> sub_gcd[N];
int a[N];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i], f[i] = f[i-1] + a[i];
  sub_gcd[0][a[0]] = 0;
  ll res = 0;
  stack<int> stk;
  segment_tree st(n);
  stk.push(0); st.add(0, 0, a[0]);
  for (int i = 1; i < n; ++i) {
    sub_gcd[i][a[i]] = 0;
    for (auto& p : sub_gcd[i-1]) {
      int nxt_gcd = __gcd(p.first, a[i]);
      sub_gcd[i][nxt_gcd] = max(sub_gcd[i][nxt_gcd], p.second + 1);
    }
    while (!stk.empty() && a[stk.top()] <= a[i]) {
      int r = stk.top(); stk.pop();
      int l = stk.empty() ? 0 : stk.top() + 1;
      st.add(l, r, -a[r]);
    }
    st.add(stk.empty() ? 0 : stk.top() + 1, i, a[i]);
    stk.push(i);
    for (auto& p : sub_gcd[i]) 
      res = max(res, abs(p.first) * (f[i] - st.get(i-p.second, i)));
  }
  cout << res;
	return 0;
}


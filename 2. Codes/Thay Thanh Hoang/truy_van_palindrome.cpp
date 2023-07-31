#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 2, M = 1e9 + 2207;

struct Hash {
  int x; unsigned long long y;
  Hash(int x = 0): x(x), y(x) {}
  Hash(int x, unsigned long long y): x(x), y(y) {}
  friend bool operator == (const Hash& u, const Hash& v) {
    return u.x == v.x && u.y == v.y;
  }
  friend bool operator != (const Hash& u, const Hash& v) {
    return !(u == v);
  }
  friend Hash operator + (Hash u, const Hash& v) {
    u.x += v.x; if (u.x >= M) u.x -= M;
    u.y += v.y;
    return u;
  }
  friend Hash operator * (Hash u, const Hash& v) {
    u.x = 1LL * u.x * v.x % M;
    u.y = u.y * v.y;
    return u;
  }
};
using ull = Hash;

ull pw[N], base = 100003;

struct Node {
  ull val = 0, rval = 0;
};

struct SegmentTree {
  int n, x, y, v;
  vector<Node> st;
  Node res; int cur_len;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 4) { build(1, 1, n); }
  
  void apply(int i, int l, int r) {
    st[i].val = st[i].rval = v;
  }
  
  void pull(int i, int l, int r) {
    int m = (l + r) / 2;
    st[i].val = st[i * 2].val * pw[r - m] + st[i * 2 + 1].val;
    st[i].rval = st[i * 2].rval + st[i * 2 + 1].rval * pw[m - l + 1];
  }
  
  void build(int i, int l, int r) {
    if (l == r)
      return v = l, apply(i, l, r), void();
    int m = (l + r) / 2;
    build(i * 2, l, m); 
    build(i * 2 + 1, m + 1, r);
    pull(i, l, r);
  }
  
  void update(int i, int l, int r) {
    if (l == r)
      return apply(i, l, r), void();
    int m = (l + r) / 2;
    if (x <= m) update(i * 2, l, m); 
    else update(i * 2 + 1, m + 1, r);
    pull(i, l, r);
  }
  
  void get(int i, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) {
      res.val = res.val * pw[r - l + 1] + st[i].val;
      res.rval = res.rval + st[i].rval * pw[cur_len];
      cur_len += r - l + 1;
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
  
  Node get(int l, int r) {
    x = l, y = r, cur_len = 0;
    res.val = res.rval = 0;
    get(1, 1, n);
    return res;
  }
  
} st;

int link[N];
vector<int> comp[N];

int find(int i) {
  if (i == link[i]) return i;
  return link[i] = find(link[i]);
}

int n, q;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q;
  
  pw[0] = 1;
  for (int i = 1; i <= n; ++i)
    pw[i] = pw[i - 1] * base,
    link[i] = i, comp[i].emplace_back(i);
  
  st = SegmentTree(n);
  
  for (int i = 0, t, l, r, x, y; i < q; ++i) {
    cin >> t;
    if (t == 1) {
      cin >> l >> r;
      int m = (l + r) / 2;
      for (;;) {
        int lo = 1, hi = m - l + 1, mid, ans = -1;
        while (lo <= hi) {
          mid = (lo + hi) / 2;
          if (st.get(l, l + mid - 1).val != st.get(r - mid + 1, r).rval) 
            ans = mid, hi = mid - 1;
          else lo = mid + 1;
        }
        if (ans == -1) break;
        int u = find(l + ans - 1), v = find(r - ans + 1);
        if (comp[u].size() < comp[v].size()) swap(u, v);
        for (int i : comp[v]) {
          st.update(i, u); 
          comp[u].emplace_back(i);
        }
        vector<int>().swap(comp[v]);
        link[v] = u;
      }
    } else {
      cin >> l >> r >> x >> y;
      if (r - l != y - x) cout << 1 << '\n';
      else cout << (st.get(l, r).val == st.get(x, y).val ? 0 : 2) << '\n';
    }
    
  }
	return 0;
}


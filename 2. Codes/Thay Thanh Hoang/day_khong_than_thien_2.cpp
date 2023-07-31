#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;
int c[N], a[N];
int n, m;

int vis[N];

array<int, 3> all[N]; int siz = 0;

struct SegmentTree {
  struct Node {
    vector<array<int, 3>> p;
    Node() { p.reserve(5); }
  };
  Node merge() {
    Node res; 
    for (int i = 0; i < siz; ++i) {
      if (vis[all[i][1]] == all[i][2]) continue;
      vis[all[i][1]] = all[i][2]; 
      res.p.emplace_back(all[i]);
      if (res.p.size() == 5) break;
    }
    for (auto& p : res.p) vis[p[1]] = -1;
    return res;
  }
  Node merge(const Node& u, const Node& v) {
    siz = 0;
    int i = 0, j = 0; siz = 0;
    while (i < u.p.size() && j < v.p.size()) {
      if (u.p[i][0] > v.p[j][0]) all[siz++] = u.p[i++];
      else all[siz++] = v.p[j++];
    }
    while (i < u.p.size()) all[siz++] = u.p[i++];
    while (j < v.p.size()) all[siz++] = v.p[j++];
    return merge();
  }
  int n, x, y, v, g;
  vector<Node> st;
  Node res;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st((n + 1) * 2) {}
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) return res = merge(res, st[k]), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    get(lc, l, m); get(rc, m+1, r);
  }
  void update(int k, int l, int r) {
    if (l == r) {
      siz = 0; int flag = 0;
      for (auto& p : st[k].p) {
        if (!flag && p[0] < v) 
          flag = 1, all[siz++] = {v, g, l};
        all[siz++] = p;
      }
      if (!flag)
        all[siz++] = {v, g, l};
      return st[k] = merge(), void();
    }
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    if (x <= m) update(lc, l, m);
    else update(rc, m+1, r);
    st[k] = merge(st[lc], st[rc]);
  }
  Node get(int l, int r) {
    x = l, y = r; res.p.clear();
    get(1, 0, n);
    return res;
  }
  Node get(int i) {
    return merge(get(0, i-1), get(i+1, m));
  }
  void add(int i, int g, int v) {
    x = i, this->g = g, this->v = v;
    update(1, 0, n);
  }
} st;


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T; cin >> T;
  while (T--) {
    cin >> n; 
    for (int i = 0; i < n; ++i)
      cin >> a[i], c[i] = a[i];
    sort(c, c + n), m = unique(c, c + n) - c;
    for (int i = 0; i <= n; ++i) vis[i] = -1;
    st = SegmentTree(m);
    st.add(0, 0, 0);
    int res = 0;
    for (int i = 0; i < n; ++i) {
      a[i] = lower_bound(c, c + m, a[i]) - c + 1;
      auto g = st.get(a[i]);
      for (auto& p : g.p) if (p[1] != a[i]) 
        st.add(a[i], p[2], p[0] + 1),
        res = max(res, p[0] + 1);
    }
    cout << res << '\n';
  }
	return 0;
}


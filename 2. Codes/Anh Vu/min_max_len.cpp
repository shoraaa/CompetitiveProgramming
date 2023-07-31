#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int M = 1e9;
void add(int& x, int y) { x += y; if (x >= M) x -= M; }
int sum(int x, int y) { x += y; if (x >= M) x -= M; return x; }
int mul(ll x, ll y) { return x * y % M; }
struct SegmentTree {
  int n, x, y;
  int tx, ty, tz;
  struct Node {
    int x, y, z, xy, yz, zx, xyz, tx = 0, ty = 0, tz = 0;
    Node(int x = 0, int y = 0, int z = 0): x(x), y(y), z(z), 
          xy(mul(x, y)), yz(mul(y, z)), zx(mul(z, x)), 
          xyz(mul(xy, z)) {}
    void merge(Node& lef, Node& rig) {
      x = sum(lef.x, rig.x), y = sum(lef.y, rig.y), z = sum(lef.z, rig.z);
      xy = sum(lef.xy, rig.xy), yz = sum(lef.yz, rig.yz), zx = sum(lef.zx, rig.zx);
      xyz = sum(lef.xyz, rig.xyz);
    }
  };
  vector<Node> st;
  vector<int> len;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2), len(n * 2) { build(1, 0, n-1); }
  void build(int k, int l, int r) {
    if (l == r) return len[k] = 1, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    build(lc, l, m), build(rc, m+1, r);
    len[k] = len[lc] + len[rc];
  }
  void apply(int k, int x, int y, int z) {
    if (x) {
      add(st[k].x, mul(x, len[k]));
      add(st[k].xy, mul(x, st[k].y));
      add(st[k].zx, mul(x, st[k].z));
      add(st[k].xyz, mul(x, st[k].yz));
      add(st[k].tx, x);
    }
    if (y) {
      add(st[k].y, mul(y, len[k]));
      add(st[k].xy, mul(y, st[k].x));
      add(st[k].yz, mul(y, st[k].z));
      add(st[k].xyz, mul(y, st[k].zx));
      add(st[k].ty, y);
    }
    if (z) {
      add(st[k].z, mul(z, len[k]));
      add(st[k].zx, mul(z, st[k].x));
      add(st[k].yz, mul(z, st[k].y));
      add(st[k].xyz, mul(z, st[k].xy));
      add(st[k].tz, z);
    }
  }
  void push(int k, int lc, int rc) {
    apply(lc, st[k].tx, st[k].ty, st[k].tz);
    apply(rc, st[k].tx, st[k].ty, st[k].tz);
    st[k].tx = st[k].ty = st[k].tz = 0;
  }
  void update(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return apply(k, tx, ty, tz), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    update(lc, l, m), update(rc, m+1, r);
    st[k].merge(st[lc], st[rc]);
  }
  void update(int l, int r, int tx, int ty, int tz) {
    if (l > r) return;
    x = l, y = r;
    assert(ty >= 0 && ty < M);
    this->tx = tx, this->ty = ty, this->tz = tz;
    update(1, 0, n-1);
  }
  int get() {
    return st[1].xyz;
  }
} st;
const int N = 5e5 + 5;
int a[N];
int n;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  stack<int> st1, st2;
  int res = 0; st = SegmentTree(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i]; 
    while (!st1.empty() && a[st1.top()] < a[i]) {
      int r = st1.top(); st1.pop();
      int l = st1.empty() ? 0 : st1.top() + 1;
      st.update(l, r, a[i] - a[r], 0, 0);
    }
    while (!st2.empty() && a[st2.top()] > a[i]) {
      int r = st2.top(); st2.pop();
      int l = st2.empty() ? 0 : st2.top() + 1;
      st.update(l, r, 0, a[i] - a[r] + M, 0);
    }
    st.update(0, i-1, 0, 0, 1);
    
    st.update(i, i, a[i], a[i], 1);
    add(res, st.get());
    st1.push(i), st2.push(i);
  }
  cout << res;
	return 0;
}


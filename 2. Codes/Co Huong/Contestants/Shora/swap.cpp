#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
const int INF = 1e9;

int a[N];
int n, k;

struct SegmentTree {
  int n, x, y, v;
  struct Node {
    int pos, lazy = 0;
    pair<int, int> val;
  };
  
  vector<Node> st;
  pair<int, int> res;
  
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 4) {
    build(1, 1, n);
  }
  
  void pull(int i) {
    st[i].val = max(st[i * 2].val, st[i * 2 + 1].val);
    st[i].pos = max(st[i * 2].pos, st[i * 2 + 1].pos);
  }
  
  void push(int i) {
    if (!st[i].lazy) return;
    int x = st[i].lazy; st[i].lazy = 0;
    st[i * 2].pos += x; st[i * 2].lazy += x;
    st[i * 2 + 1].pos += x; st[i * 2 + 1].lazy += x;
  }
  
  void build(int i, int l, int r) {
    if (l == r) {
      st[i].pos = l;
      st[i].val = make_pair(a[l], -l);
      return;
    }
    int m = (l + r) / 2;
    build(i * 2, l, m);
    build(i * 2 + 1, m + 1, r);
    pull(i);
  }
  
  void climb(int i, int l, int r) {
    if (l == r) {
      return;
    }
    int m = (l + r) / 2;
    push(i);
    if (st[i * 2].pos > v) climb(i * 2, l, m);
    else {
      res = max(res, st[i * 2].val);
      climb(i * 2 + 1, m + 1, r);
    }
  }
  
  pair<int, int> get(int k) {
    res = make_pair(-INF, 0); 
    v = k;
    if (st[1].pos <= v) {
      return st[1].val;
    }
    climb(1, 1, n);
    return res;
  }
  
  void update(int i, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) {
      st[i].pos += 1;
      st[i].lazy += 1;
      return;
    }
    int m = (l + r) / 2;
    push(i);
    update(i * 2, l, m);
    update(i * 2 + 1, m + 1, r);
    pull(i);
  }
  
  void update(int l, int r) {
    x = l, y = r;
    update(1, 1, n);
  }
  
  void erase(int i, int l, int r) {
    if (l == r) {
      st[i].val = make_pair(-INF, 0);
      return;
    }
    push(i);
    int m = (l + r) / 2;
    if (x <= m) erase(i * 2, l, m);
    else erase(i * 2 + 1, m + 1, r);
    pull(i);
  }
  
  void erase(int i) {
    x = i;
    erase(1, 1, n);
  }
  
  void get_pos(int i, int l, int r) {
    if (l == r) {
      v = st[i].pos;
      return;
    }
    push(i);
    int m = (l + r) / 2;
    if (x <= m) get_pos(i * 2, l, m);
    else get_pos(i * 2 + 1, m + 1, r);
  }
  
  int get_pos(int i) {
    x = i;
    get_pos(1, 1, n);
    return v;
  }
  
} st;

#define fi first
#define se second

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("swap.inp", "r"))
    freopen("swap.inp", "r", stdin),
    freopen("swap.out", "w", stdout);
    
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  st = SegmentTree(n);
  
  for (int i = 1; i <= n; ++i) {
    auto p = st.get(i + k);
    int j = -p.se; 
    k -= st.get_pos(j) - i;
    cout << a[j] << ' ';
    st.erase(j);
    st.update(1, j);
  }
  
	return 0;
}


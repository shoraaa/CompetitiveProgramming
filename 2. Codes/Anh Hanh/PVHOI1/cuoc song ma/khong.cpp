#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll pwof(ll x, ll k) {
  ll res = 0;
  while (x > 0 && x % k == 0) x /= k, res++;
  return res;
  
}

ll eval(ll x) {
  // 0 + 1 + .. + x
  return x * (x + 1) / 2;
}


const int N = 200315;
int a[N], b[N];
int n, q;

void task1() {
  for (int i = 1, x; i <= n; ++i) {
    cin >> x;
    a[i] = pwof(x, 2); 
    b[i] = pwof(x, 5);
  }
  char ch; 
  ll l, r, x, y;
  while (q--) {
    cin >> ch >> l >> r;
    if (ch == 'A' || ch == 'G') {
      cin >> x >> y;
      int x2 = pwof(x, 2), x5 = pwof(x, 5), y2 = pwof(y, 2), y5 = pwof(y, 5);
      for (int i = l; i <= r; ++i) {
        if (ch == 'A') {
          a[i] += pwof(x + (i - l) * y, 2);
          b[i] += pwof(x + (i - l) * y, 5);
        } else {
          a[i] += x2, b[i] += x5;
          x2 += y2, x5 += y5;
        }
      }
    } else {
      x = y = 0;
      for (int i = l; i <= r; ++i)
        x += a[i], y += b[i];
      cout << min(x, y) << ' ';
    }
  }
  exit(0);
}

struct SegmentTree {
  int n, x, y;
  struct Node {
    ll sum = 0, lazy = 0, z = 0;
  };
  vector<Node> st;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 4) {}
  
  ll z, cur_len, res;
  
  void apply2(int i, int l, int r) {
    ll sum = z * (eval(r - l) + cur_len * (r - l + 1));
    st[i].z += z;
    st[i].sum += sum;
    st[i].lazy += cur_len * z;
    cur_len += r - l + 1;
  }
  
  void push(int i, int l, int r) {
    int m = (l + r) / 2; 
    
    ll z = st[i].z;
    if (z) {
      st[i].z = 0;
      st[i * 2].z += z;
      st[i * 2 + 1].z += z;
    }
    
    ll lazy = st[i].lazy, val;
    if (lazy > 0 || z > 0) {
      st[i].lazy = 0;
      
      val = z * eval(m - l) + lazy * (m - l + 1); 
      st[i * 2].sum += val;
      st[i * 2].lazy += lazy;
      
      lazy += z * (m - l + 1);
      val = z * eval(r - m - 1) + lazy * (r - m);
      st[i * 2 + 1].sum += val;
      st[i * 2 + 1].lazy += lazy; 
    }
  }
  
  void update1(int i, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return st[i].sum += z * (r - l + 1), st[i].lazy += z, void();
    int m = (l + r) / 2;
    push(i, l, r);
    update1(i * 2, l, m);
    update1(i * 2 + 1, m + 1, r);
    st[i].sum = st[i * 2].sum + st[i * 2 + 1].sum;
  }
  
  void update2(int i, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return apply2(i, l, r), void();
    int m = (l + r) / 2;
    push(i, l, r);
    update2(i * 2, l, m);
    update2(i * 2 + 1, m + 1, r);
    st[i].sum = st[i * 2].sum + st[i * 2 + 1].sum;
  }
  
  void get(int i, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return res += st[i].sum, void();
    int m = (l + r) / 2;
    push(i, l, r);
    get(i * 2, l, m);
    get(i * 2 + 1, m + 1, r);
  }
  
  void add1(int l, int r, int z) {
    x = l, y = r, this->z = z;
    update1(1, 1, n);
  }
  
  void add2(int l, int r, int z) {
    x = l, y = r, this->z = z;
    cur_len = 0;
    update2(1, 1, n);
  }
  
  ll get(int l, int r) {
    x = l, y = r, res = 0;
    get(1, 1, n);
    return res;
  }
  
} st_2, st_5;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("khong.inp", "r"))
    freopen("khong.inp", "r", stdin),
    freopen("khong.out", "w", stdout);
  int task; cin >> task; 
  cin >> n >> q;
  
  if (task == 1) task1();
  
  st_2 = st_5 = SegmentTree(n);
  
  for (int i = 1, x; i <= n; ++i) {
    cin >> x;
    st_2.add1(i, i, pwof(x, 2));
    st_5.add1(i, i, pwof(x, 5));
  }
  
  char ch;
  for (int i = 0, l, r, x, y; i < q; ++i) {
    cin >> ch;
    if (ch == 'A' || ch == 'G') {
      cin >> l >> r >> x >> y;
      st_2.add1(l, r, pwof(x, 2));
      st_5.add1(l, r, pwof(x, 5));
      if (ch == 'G') {
        st_2.add2(l, r, pwof(y, 2));
        st_5.add2(l, r, pwof(y, 5));
      }
    } else {
      cin >> l >> r;
      cout << min(st_2.get(l, r), st_5.get(l, r)) << ' ';
    }
  } 
  
	return 0;
}


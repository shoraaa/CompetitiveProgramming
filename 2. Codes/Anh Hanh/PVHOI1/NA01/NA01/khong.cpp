#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 200315;
int a[N], b[N];
int n, q;

int val2(ll x) {
  int res = 0;
  while (x > 0 && x % 2 == 0) x /= 2, res++;
  return res;
}
int val5(ll x) {
  int res = 0;
  while (x > 0 && x % 5 == 0) x /= 5, res++;
  return res;
}

namespace task1 {
  void solve() {
    for (int t = 0, l, r, x, y; t < q; ++t) {
      char ch;
      cin >> ch >> l >> r; l--; r--; 
      if (ch == 'A' || ch == 'G') {
        cin >> x >> y; ll cur_2 = val2(x), cur_5 = val5(x);
        for (int i = l; i <= r; ++i) {
          if (ch == 'A') {
             ll z = x + ll(i - l) * y;
             a[i] += val2(z), b[i] += val5(z);
          } else {
            // x * y ^(t-l)
            if (t != l) cur_2 += val2(y), cur_5 += val5(y);
            a[i] += cur_2, b[i] += cur_5;
          }
          
        }
      } else if (ch == 'C') {
        int x = 0, y = 0;
        for (int i = l; i <= r; ++i)
          x += a[i], y += b[i];
        cout << min(x, y) << ' ';
      }
    }
  }
}

namespace task2 {
  struct SegmentTree {
    int n, x, y, v, res;
    vector<int> st, lz;
    SegmentTree() = default;
    SegmentTree(int n): n(n), st(n * 2), lz(n * 2) {}
    void push(int k, int lc, int rc, int m, int l, int r) {
      if (!lz[k]) return;
      int x = lz[k]; lz[k] = 0;
      st[lc] += (m - l + 1) * x, lz[lc] += x;
      st[rc] += (r - l) * x, lz[rc] += x;
    }
    void update(int k, int l, int r) {
      if (l > y || r < x) return;
      if (l >= x && r <= y) return st[k] += v * (r - l + 1), lz[k] += v, void();
      int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
      push(k, lc, rc, m, l, r); update(lc, l, m), update(rc, m + 1, r);
      st[k] = st[lc] + st[rc];
    }
    void get(int k, int l, int r) {
      if (l > y || r < x) return;
      if (l >= x && r <= y) return res += st[k], void();
      int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
      push(k, lc, rc, m, l, r); get(lc, l, m), get(rc, m + 1, r);
    } 
    void add(int l, int r, int v) {
      x = l, y = r, this->v = v;
      update(1, 0, n - 1);
    }
    int get(int l, int r) {
      x = l, y = r, res = 0;
      get(1, 0, n - 1);
      return res;
    }
  } st2, st5;
  
  void solve() {
    st2 = st5 = SegmentTree(n);
    for (int i = 0; i < n; ++i) 
      st2.add(i, i, a[i]),
      st5.add(i, i, b[i]);
    for (int t = 0, l, r, x, y; t < q; ++t) {
      char ch;
      cin >> ch >> l >> r; l--; r--; 
      if (ch == 'A' || ch == 'G') {
        cin >> x >> y; // y == 0
        st2.add(l, r, val2(x));
        st5.add(l, r, val5(x));               
      } else if (ch == 'C') {
        cout << min(st2.get(l, r), st5.get(l, r)) << ' ';
      }
    }
  }
  
}

namespace task3 {
  
  ll S(int n) {
    return n * (n + 1) / 2;
  }
  ll S(int l, int r) {
    return S(r) - S(l - 1);
  }
  
  struct SegmentTree {
    int n, x, y, v, res;
    struct Node {
      int sum = 0, lazy = 0, val = 0;
    };
    vector<Node> st;
    SegmentTree() = default;
    SegmentTree(int n): n(n), st(n * 2) {}
    void push(int k, int lc, int rc, int m, int l, int r) {
      int lazy = st[k].lazy; st[k].lazy = 0;
      int val = st[k].val; st[k].val = 0;
      
      
      ll tmp = S(1, m - l) * val;
      st[lc].sum += tmp; st[lc].val += val;
      st[lc].sum += lazy * (m-l+1), st[lc].lazy += lazy;
      
      tmp = S(m - l + 1, r - l) * val;
      st[rc].sum += tmp; st[rc].val += val;
      st[rc].sum += lazy * (r-m), st[rc].lazy += lazy;
      
      if (m-l+1==3&&r==3) {
        cerr << v << ' ' << S(m-l+1, r-l) << ' ' << tmp << " WA\n";
      }
      
    }
    void update1(int k, int l, int r) {
      if (l > y || r < x) return;
      if (l >= x && r <= y) return st[k].sum += v * (r - l + 1), st[k].lazy += v, void();
      int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
      push(k, lc, rc, m, l, r); update1(lc, l, m), update1(rc, m + 1, r);
      st[k].sum = st[lc].sum + st[rc].sum;
    }
    
    void update2(int k, int l, int r) {
      if (l > y || r < x) return;
      if (l >= x && r <= y) {
        st[k].sum += S(r - l) * v;
        st[k].val += v;
        return;
      }
      int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
      push(k, lc, rc, m, l, r); 
      update2(lc, l, m);
      v *= (m - l + 1);
      update2(rc, m + 1, r);
      st[k].sum = st[lc].sum + st[rc].sum;
    }
    
    void get(int k, int l, int r) {
      if (l > y || r < x) return;
      if (l >= x && r <= y) return res += st[k].sum, void();
      int m = l + r >> 1, lc = k + 1, rc = k + (m - l + 1) * 2;
      push(k, lc, rc, m, l, r); get(lc, l, m), get(rc, m + 1, r);
    } 
    void add(int l, int r, int v) {
      x = l, y = r, this->v = v;
      update1(1, 0, n - 1);
    }
    void update(int l, int r, int v) {
      x = l, y = r, this->v = v;
      if (!v) return;
      update2(1, 0, n - 1);
      cerr << st[1].sum << '\n';
    }
    int get(int l, int r) {
      x = l, y = r, res = 0;
      get(1, 0, n - 1);
      return res;
    }
  } st2, st5;
  
  void solve() {
    st2 = st5 = SegmentTree(n);
    
    for (int i = 0; i < n; ++i) 
      st2.add(i, i, a[i]),
      st5.add(i, i, b[i]);
    for (int t = 0, l, r, x, y; t < q; ++t) {
      char ch;
      cin >> ch >> l >> r; l--; r--; 
      if (ch == 'A' || ch == 'G') {
        cin >> x >> y; // y == 0
        st2.add(l, r, val2(x));
        st5.add(l, r, val5(x));         
        if (ch == 'G' && y != 1) {
          st2.update(l + 1, r, val2(y));
          st5.update(l + 1, r, val5(y));
        }      
      } else if (ch == 'C') {
        cout << min(st2.get(l, r), st5.get(l, r)) << ' ';
      }
    }
    
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("khong.inp", "r"))
    freopen("khong.inp", "r", stdin),
    freopen("khong.out", "w", stdout);
  
  int task; cin >> task;
  cin >> n >> q;
  for (int i = 0, x; i < n; ++i) {
    cin >> x;
    a[i] = val2(x), b[i] = val5(x);
  }
  if (task == 1) task1::solve();
  else if (task == 2) task2::solve();
  else if (task == 3) task3::solve();
	return 0;
}


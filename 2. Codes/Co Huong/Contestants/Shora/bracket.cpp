#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5;
string s;
int n, q;
int f[N];

struct SegmentTree {
  int n, x, y;
  struct Node {
    int val, lazy = 0;
  };
  vector<Node> st;
  int v;
  
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 4) {
    build(1, 1, n);
  }
  
  void pull(int i) {
    st[i].val = min(st[i * 2].val, st[i * 2 + 1].val);
  }
  
  void build(int i, int l, int r) {
    if (l == r) {
      st[i].val = f[l];
      return;
    }
    int m = (l + r) / 2;
    build(i * 2, l, m);
    build(i * 2 + 1, m + 1, r);
    pull(i);
  }
  
  void push(int i) {
    if (!st[i].lazy) return;
    int x = st[i].lazy; st[i].lazy = 0;
    
    st[i * 2].val += x; st[i * 2].lazy += x;
    st[i * 2 + 1].val += x; st[i * 2 + 1].lazy += x;
  }
  
  void update(int i, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) {
      st[i].val += v;
      st[i].lazy += v;
      return;
    }
    push(i);
    int m = (l + r) / 2;
    update(i * 2, l, m);
    update(i * 2 + 1, m + 1, r);
    pull(i);
  }
  
  void add(int l, int r, int v) {
    x = l, y = r, this->v = v;
    update(1, 1, n);
  }
  
  int pos;
  void climb(int i, int l, int r) {
    if (l == r) {
      pos = l + 1;
      return;
    }
    push(i);
    int m = (l + r) / 2;
    if (st[i * 2 + 1].val < 2) climb(i * 2 + 1, m + 1, r);
    else climb(i * 2, l, m);
  }
  
  int get() {
    climb(1, 1, n);
    return pos;
  }
  
} st;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("bracket.inp", "r"))
    freopen("bracket.inp", "r", stdin),
    freopen("bracket.out", "w", stdout);
  
  cin >> n >> q >> s;
  s = ' ' + s;
  
  set<int> close;
  for (int i = 1; i <= n; ++i) {
    f[i] = f[i - 1] + (s[i] == '(' ? 1 : -1);
    if (s[i] == ')') {
      close.insert(i);
    }
  }
  
  st = SegmentTree(n);
  
  while (q--) {
    int i; cin >> i;
    if (s[i] == '(') {
      s[i] = ')'; 
      close.insert(i);
      st.add(i, n, -2);
      
      int j = *close.begin();
      close.erase(j);
      s[j] = '(';
      st.add(j, n, +2);
    } else {
      s[i] = '('; 
      close.erase(i);
      st.add(i, n, +2);
      
      int j = st.get();
      s[j] = ')';
      close.insert(j);
      st.add(j, n, -2);
    }
  }
  
  cout << s.substr(1, n);
  
  
	return 0;
}


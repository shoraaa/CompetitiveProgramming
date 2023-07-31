#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 5;
string s;

int pos[N], ord[N];

int flag =0 ;

struct SegmentTree {
  int n, x, v;
  struct Node {
    int cnt_0 = 0, cnt_1 = 0;
  };
  vector<Node> st;
  
  SegmentTree(int n): n(n), st(n * 4) {
    build(1, 1, n);
  }
  
  void build(int i, int l, int r) {
    if (l == r) {
      if (s[ord[l]] == '0') st[i].cnt_0 = 1;
      else st[i].cnt_1 = 1;
      return;
    }
    
    int m = (l + r) / 2;
    build(i * 2, l, m);
    build(i * 2 + 1, m + 1, r);
    
    st[i].cnt_0 = st[i * 2].cnt_0 + st[i * 2 + 1].cnt_0;
    st[i].cnt_1 = st[i * 2].cnt_1 + st[i * 2 + 1].cnt_1;
    
  }
  
  void update(int i, int l, int r) {
    if (l == r) {
      
      if (v == 0) st[i].cnt_0++, st[i].cnt_1--;
      else st[i].cnt_0--, st[i].cnt_1++;
      
      return;
    }
    int m = (l + r) / 2;
    if (x <= m) update(i * 2, l, m);
    else update(i * 2 + 1, m + 1, r);
    
    st[i].cnt_0 = st[i * 2].cnt_0 + st[i * 2 + 1].cnt_0;
    st[i].cnt_1 = st[i * 2].cnt_1 + st[i * 2 + 1].cnt_1;
    
  }
  
  void update(int i, int v) {
    this->v = v;
    x = i;
    
    update(1, 1, n);
  }
  
  int cur_0, cur_1;
  void get_pos(int i, int l, int r) {
    if (l == r) {
      if (cur_0 + st[i].cnt_0 - v <= cur_1 - st[i].cnt_1) {
        x = l;
      }
      return;
    }
    
    int m = (l + r) / 2;
    if (cur_0 + st[i * 2].cnt_0 - v <= cur_1 - st[i * 2].cnt_1) {
      x = m;
      cur_0 += st[i * 2].cnt_0;
      cur_1 -= st[i * 2].cnt_1;
      get_pos(i * 2 + 1, m + 1, r);
    } else {
      get_pos(i * 2, l, m);
    }
    
    
  }
  
  
  int get_pos(int cnt) {
    v = cnt;
    x = 0;
    
    cur_0 = 0, cur_1 = st[1].cnt_1;
    
    get_pos(1, 1, n);
    return x;
  }
  
  void get_sum(int i, int l, int r) {
    if (l == r) {
      v += st[i].cnt_0;
      return;
    }
    int m = (l + r) / 2;
    if (x <= m) get_sum(i * 2, l, m);
    else v += st[i * 2].cnt_0, get_sum(i * 2 + 1, m + 1, r);
    
  }
  
  int get_sum(int i) {
    
    if (i == 0) {
      return 0;
    }
    
    x = i;
    v = 0;
    
    get_sum(1, 1, n);
    return v;
  }
  
  
  
};

int n, m, q, k = 0;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> q;
  cin >> s; s = ' ' + s;
  
  set<int> st;
  for (int i = 1; i <= n; ++i) {
    st.insert(i);
  }
  
  for (int i = 1, l, r; i <= m; ++i) {
    cin >> l >> r;
    for (auto it = st.lower_bound(l);;) {
      if (it == st.end() || *it > r) break;
      ord[++k] = *it;
      it = st.erase(it);
    }
  }
  
  for (int i = 1; i <= k; ++i) {
    pos[ord[i]] = i;
  }
  
  int cnt = 0;
  for (int i : st) {
    cnt += s[i] == '1';
  }
  
  SegmentTree sg(k);
  
  for (int i = 1, p; i <= q; ++i) {
    cin >> p;
    
    flag = p == 8;
    
    if (s[p] == '0') {
      s[p] = '1';
      if (st.count(p)) cnt++;
      else sg.update(pos[p], 1);
    } else {
      s[p] = '0';
      if (st.count(p)) cnt--;
      else sg.update(pos[p], 0);
    }
   
    cout << sg.get_sum(sg.get_pos(cnt)) << '\n';
    
  }
  
  
  
	return 0;
}


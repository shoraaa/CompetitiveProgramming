#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
int n, m, start, d;
int a[N], c[N];

ll ans[N];

struct SegmentTree {
  int n, v, sgn; ll res;
  vector<int> cnt; vector<ll> val;
  SegmentTree() = default;
  SegmentTree(int n): n(n), val(n*2), cnt(n*2) {}
  void get(int k, int l, int r) {
    if (l == r) {
      if (v <= cnt[k]) res += c[l] * v, v = 0;
      else v -= cnt[k], res += val[k];
      return;
    }
    int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
    if (v <= cnt[rc]) get(rc, m+1, r);
    else v -= cnt[rc], res += val[rc], get(lc, l, m);
  }
  void update(int k, int l, int r) {
    val[k] += c[v] * sgn, cnt[k] += sgn;
    if (l == r) return void();
    int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
    if (v <= m) update(lc, l, m);
    else update(rc, m+1, r);
  }
  void update(int v, int sgn) {
    this->v = v, this->sgn = sgn;
    update(1, 0, n-1);
  }
  ll get(int v) {
    this->v = v; res = 0;
    get(1, 0, n-1);
    return res;
  }
} st;

void call(int l, int r, int x, int y) {
  if (l > r) return;
  int m1 = l + r >> 1, m2 = -1;
  
  for (int i = r; i >= m1; --i) 
    st.update(a[i], 1);
    
  for (int i = x; i <= y; ++i) {
    int k = d - min(start - m1, i - start) - (i - m1);
    if (k < 0) break;
    st.update(a[i], 1); int val;

    if (st.get(k) > ans[m1])  
      ans[m1] = st.get(k), m2 = i;
  }

  for (int i = x; i <= y; ++i) {
    int k = d - min(start - m1, i - start) - (i - m1);
    if (k < 0) break;
    st.update(a[i], -1);
  }
  
  if (m2 == -1) {
    for (int i = r; i >= m1; --i) 
      st.update(a[i], -1);
    return call(m1 + 1, r, x, y), void();
  }
  
  call(l, m1 - 1, x, m2);
  
  for (int i = x; i < m2; ++i)
    st.update(a[i], 1);
  
  for (int i = r; i >= m1; --i) 
    st.update(a[i], -1);
  
  call(m1 + 1, r, m2, y);
  
  for (int i = x; i < m2; ++i)
    st.update(a[i], -1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("holiday.inp", "r"))
    freopen("holiday.inp", "r", stdin),
    freopen("holiday.out", "w", stdout);
  cin >> n >> start >> d;
  for (int i = 0; i < n; ++i)
    cin >> a[i], c[i] = a[i];
  sort(c, c + n); m = unique(c, c + n) - c;
  st = SegmentTree(m);
  for (int i = 0; i < n; ++i)
    a[i] = lower_bound(c, c + m, a[i]) - c;
  call(0, start, start + 1, n-1);
  
  ll res = 0;
  for (int i = 0; i <= start; ++i)
    res = max(res, ans[i]);
    
  for (int i = start; i < n; ++i) {
    int k = d - (i - start);
    if (k < 0) break;
    st.update(a[i], 1);
    res = max(res, st.get(k));
  }  
  st = SegmentTree(m);
  for (int i = start; ~i; --i) {
    int k = d - (start - i);
    if (k < 0) break;
    st.update(a[i], 1);
    res = max(res, st.get(k));
  }
    
  cout << res;
	return 0;
}


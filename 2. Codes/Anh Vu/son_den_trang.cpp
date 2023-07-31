#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5, inf = 1e9;
struct SegmentTree {
  int n, x, y, v, res;
  vector<int> st, lz;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2, inf), lz(n * 2) {}
  void push(int k, int lc, int rc) {
    int v = lz[k]; lz[k] = 0;
    st[lc] += v, lz[lc] += v;
    st[rc] += v, lz[rc] += v;
  }
  void add(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return st[k]++, lz[k]++, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    add(lc, l, m), add(rc, m+1, r);
    st[k] = min(st[lc], st[rc]);
  }
  void set(int k, int l, int r) {
    if (l > x || r < x) return;
    if (l == r) 
      return st[k] = v, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    set(lc, l, m), set(rc, m+1, r);
    st[k] = min(st[lc], st[rc]);
  }
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return res = min(res, st[k]), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    get(lc, l, m), get(rc, m+1, r);
  }
  void add(int l, int r) {
    x = l, y = r;
    add(1, 1, n);
  } 
  void set(int i, int v) {
    x = i; this->v = v;
    set(1, 1, n);
  }
  int get(int l, int r) {
    x = l, y = r, res = inf;
    get(1, 1, n);
    return res;
  }
} st[2];

int dp[N], a[N], b[N];
int n, k;

int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  char c;
  for (int i = 1; i <= n; ++i) 
    cin >> c, a[i] = c == 'W';
  for (int i = 1; i <= n; ++i) 
    cin >> c, b[i] = c == 'W';
  st[0] = st[1] = SegmentTree(n);
  for (int i = 1; i <= n; ++i) {
    if (b[i] != b[i-1]) 
      st[!b[i]].add(1, i-1);
    st[b[i]].set(i, dp[i-1]);
    if (a[i] == b[i]) dp[i] = dp[i-1];
    else dp[i] = st[b[i]].get(max(1, i - k + 1), i) + 1;
  }
  cout << dp[n] << '\n';
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int inf = 1e9;
const int N = 2e5 + 5;
struct SegmentTree {
  int n, x, y, v, res;
  int st[N * 2];
  SegmentTree() = default;
  SegmentTree(int n): n(n) {}
  void get(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y)
      return res = min(res, st[k]), void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    get(lc, l, m), get(rc, m+1, r);
  }
  void update(int k, int l, int r) {
    if (l == r)
      return st[k] = v, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    if (x <= m) update(lc, l, m);
    else update(rc, m+1, r);
    st[k] = min(st[lc], st[rc]);
  }
  int get(int l, int r) {
    x = l, y = r, res = inf;
    get(1, 1, n);
    if (res == inf) return -1;
    return res;
  }
  void update(int i, int v) {
    x = i, this->v = v;
    update(1, 1, n);
  }
} st;
int a[N], L[N], R[N], val[N];
ll f[N], res[N], sum[N], bit[N];
pair<int, int> sorted[N];
int n, q;

ll get(int i) {
  ll res = 0;
  for (; i; i -= i & -i)
    res += bit[i];
  return res;
}

void add(int i, int v) {
  for (; i <= n; i += i & -i)
    bit[i] += v;
}
int pos[N];
void find_nxt() {
  memset(st.st, 0x3f, sizeof(st.st));
  stable_sort(pos, pos + q, [](int u, int v) {
    return sum[u] > sum[v];
  });
  int i = n-1;
  for (int p : pos) if (!~res[p]) {
    while (~i && sorted[i].first > sum[p] + 1)
      st.update(sorted[i].second, sorted[i].first), i--;
    val[p] = st.get(L[p], R[p]);
    if (val[p] == -1) 
      res[p] = f[R[p]] - f[L[p] - 1] + 1;
  }
}

void find_sum() {
  memset(bit, 0, sizeof(bit));
  sort(pos, pos + q, [&](int u, int v) {
    return val[u] < val[v];
  });
  int i = 0;
  for (int p : pos) if (!~res[p]) {
    while (i < n && sorted[i].first < val[p]) 
      add(sorted[i].second, sorted[i].first), i++;
    sum[p] = get(R[p]) - get(L[p] - 1);
    if (val[p] > sum[p] + 1) 
      res[p] = sum[p] + 1;
  }
}

signed main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q; st.n = n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], f[i] = f[i-1] + a[i],
		sorted[i-1] = {a[i], i};
  stable_sort(sorted, sorted + n);.
  for (int i = 0, l, r; i < q; ++i) 
    cin >> l >> r, pos[i] = i,
    L[i] = l, R[i] = r, 
    res[i] = -1, sum[i] = 0;
  int cnt = 0;
  for (int i = 0; i < 30; ++i) {
    find_nxt(), find_sum();
    int flag = 0;
    for (int i = 0; i < q; ++i)
      if (res[i] == -1)  { flag = 1; break; }
    if (!flag) break;
  }
  for (int i = 0; i < q; ++i)
    cout << res[i] << '\n';
	return 0;
}



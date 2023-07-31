#include<bits/stdc++.h>
using namespace std;
using ll = long long;
void file() {
	const string FILE_NAME = "sseq";
	if (!fopen((FILE_NAME + ".inp").c_str(), "r")) return;
	freopen((FILE_NAME + ".inp").c_str(), "r", stdin);
	freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
struct SegmentTree {
  int n, x, y, v;
  vector<ll> st, lz;
  SegmentTree() = default;
  SegmentTree(int n): n(n), st(n * 2), lz(n * 2) {}
  void push(int k, int lc, int rc) {
    if (!lz[k]) return;
    ll w = lz[k]; lz[k] = 0;
    st[lc] += w, lz[lc] += w;
    st[rc] += w, lz[rc] += w;
  }
  void update(int k, int l, int r) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) 
      return st[k] += v, lz[k] += v, void();
    int m = l+r>>1, lc = k+1, rc = k+(m-l+1)*2;
    push(k, lc, rc);
    update(lc, l, m), update(rc, m+1, r);
    st[k] = max(st[lc], st[rc]);
  }
  void add(int l, int r, int v) {
    x = l, y = r, this->v = v;
    update(1, 1, n);
  }
} st;
const int N = 1e6;
vector<pair<int, int>> lef[N + 5];
int n;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0); file();
  cin >> n; st = SegmentTree(N);
  for (int i = 0, l, r, w; i < n; ++i) 
    cin >> l >> r >> w, 
    lef[r].emplace_back(l, w);
  ll res = 0;
  for (int r = 1; r <= N; ++r) {
    for (auto& p : lef[r]) st.add(1, p.first, p.second);
    res = max(res, st.st[1]);
  }
  cout << res;
	return 0;
}


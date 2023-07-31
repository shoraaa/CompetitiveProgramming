#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e4 + 5;
int a[N], up[N][16], down[N][16];
int n;

int jump(int nxt[][16], int pos, int len) {
  for (int i = 15; ~i; --i) if (len >> i & 1)
    pos = nxt[pos][i];
  return pos;
}

int check(int len) {
  // ton tai day do dai 2*len+1
  for (int i = 0; i < n; ++i) {
    // day bat dau tai a[i], nhay den a[i] + len, roi nhay lui xuong a[i] + 2*len
    if (jump(down, jump(up, i, len), len) < n) return 1;
  }
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("lhseq.inp", "r"))
    freopen("lhseq.inp", "r", stdin),
    freopen("lhseq.out", "w", stdout);
  
  int T; cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 0; i < n; ++i)
      cin >> a[i];
    map<int, int> last; 
    for (int i = n-1; ~i; --i) 
      up[i][0] = last.count(a[i] + 1) ? last[a[i] + 1] : n,
      down[i][0] = last.count(a[i] - 1) ? last[a[i] - 1] : n,
      last[a[i]] = i;
    up[n][0] = down[n][0] = n;
    for (int j = 1; j < 16; ++j) for (int i = 0; i <= n; ++i)
      up[i][j] = up[up[i][j - 1]][j - 1],
      down[i][j] = down[down[i][j - 1]][j - 1];
    int lo = 1, hi = n, mid, ans = -1;
    while (lo <= hi) {
      mid = lo + hi >> 1;
      if (check(mid))
        ans = mid,
        lo = mid + 1;
      else
        hi = mid - 1;
    }
    if (ans == -1) cout << -1;
    else cout << n - (ans*2+1) << '\n';
  }
	return 0;
}


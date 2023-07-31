#include <bits/stdc++.h>
using namespace std;
void file() {
  const string FILE_NAME = "parkour";
  freopen((FILE_NAME + ".in").c_str(), "r", stdin);
  freopen((FILE_NAME + ".out").c_str(), "w", stdout);
}
using ll = long long;
using ld = long double;
const int oo = 1e9;
const int N = 1e6;
const ld eps = 1e-9;
int d[N], u[N], a[N], b[N], h[N], min_d[N], min_u[N];
int n, m;
int check(ld x) {
  ld cl = 0, cr = 0; // khoang ma i-1 co the nam trong
  for (int i = 0; i < n; ++i) {
    // h[i] phai nam trong khoang [h[i-1] - min(di), h[i-1] + min(ui)]
    // voi moi i phai nhay tu i->i+1
    ld nl = cl - min_d[i], nr = cr + min_u[i];
    ld l = h[i] - x, r = h[i] + x;
    if (max(l, nl) - min(r, nr) > eps) return 0;
    cl = max(l, nl); cr = min(r, nr);
  }
  return 1;
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  file();
  int T;
  cin >> T;
  cout << fixed << setprecision(6);
  while (T--) {
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
      cin >> h[i];
    for (int i = 0; i < m; ++i) {
      cin >> a[i] >> b[i] >> u[i] >> d[i]; a[i]--; b[i]--;
      if (a[i] > b[i]) swap(a[i], b[i]), swap(d[i], u[i]);
    }
    // h1 - di <= h2 <= h1 + ui
    // <>> giua 2 cot lien tiep ma ai->bi phai thoa man 2 cai tren
    memset(min_d, 0x3f, sizeof(min_d));
    memset(min_u, 0x3f, sizeof(min_u));
    for (int i = 0; i < m; ++i)
      for (int j = a[i] + 1; j <= b[i]; ++j)
        min_d[j] = min(min_d[j], d[i]),
        min_u[j] = min(min_u[j], u[i]);
    ld lo = 0, hi = 1e7, mid, ans = -1;
    for (int r = 0; r < 50; ++r) {
      mid = (lo + hi) / 2;
      if (check(mid)) {
        ans = mid; 
        hi = mid;
      } else {
        lo = mid;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}

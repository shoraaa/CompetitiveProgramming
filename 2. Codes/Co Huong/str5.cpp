#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 2e5 + 5;

const int M = 1e9 + 7;
int sum(int x, int y) { x += y; if (x >= M) x -= M; return x; }
int dif(int x, int y) { x -= y; if (x < 0) x += M; return x; }
int mul(ll x, ll y) { return x * y % M; }
struct Hash {
  int x; ull y;
  Hash(int x = 0): x(x), y(x) {}
  Hash(int x, ull y): x(x), y(y) {}
  Hash operator + (const Hash& h) { return {sum(x, h.x), y + h.y}; }
  Hash operator - (const Hash& h) { return {dif(x, h.x), y - h.y}; }
  Hash operator * (const Hash& h) { return {mul(x, h.x), y * h.y}; }
  bool operator == (const Hash& h) { return x == h.x && y == h.y; }
  friend ostream& operator << (ostream& os, const Hash& h) {
    return os << '(' << h.x << ',' << h.y << ')';
  }
} base(31, 37), pw[N];
struct String {
  int n;
  vector<Hash> h, h2;
  String() = default;
  String(string& s) {
    n = s.size(); s = s + s;
    h.resize(n * 2 + 1), h2.resize(n * 2 + 2);
    for (int i = 1; i <= n * 2; ++i) 
      h[i] = h[i-1] * base + (s[i-1] - 'a' + 1);
    for (int i = n * 2; i; --i)
      h2[i] = h2[i+1] * base + (s[i-1] - 'a' + 1);
  }
  
  Hash get(int l, int r) {
    if (l >= r) return h2[r] - h2[l + 1] * pw[l - r + 1];
    return h[r] - h[l - 1] * pw[r - l + 1];
  }
  
  
} a[5];
int n;
#define fi first
#define se second
int check(int len) {
  map<pair<int, ull>, int> cnt;
  for (int i = 0; i < n; ++i) {
    map<pair<int, ull>, bool> cur;
    for (int j = 1; j <= a[i].n; ++j) {
      Hash h = a[i].get(j, j + len - 1);
      Hash r = a[i].get(j + len - 1, j);
      cur[{h.x, h.y}] = 1;
      cur[{r.x, r.y}] = 1;
    }
    for (auto& p : cur) 
      cnt[p.fi]++;
  }
  for (auto& p : cnt)
    if (p.se == n) return 1;
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("str5.inp", "r"))
    freopen("str5.inp", "r", stdin),
    freopen("str5.out", "w", stdout);
  pw[0] = 1;
  for (int i = 1; i < N; ++i)
    pw[i] = pw[i-1] * base;
  cin >> n; string t;
  int lo = 1, hi = 1e9, mid, ans = 0;
  for (int i = 0, m; i < n; ++i) {
    cin >> t; hi = min(hi, int(t.size()));
    a[i] = String(t);
  }
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid)) 
      ans = mid, lo = mid + 1;
    else
      hi = mid - 1;
  }
  cout << ans << '\n';
	return 0;
}


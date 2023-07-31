#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int M = 1e9 + 123;
inline int sum(int x, int y) { x += y; if (x >= M) x -= M; return x; }
inline int dif(int x, int y) { x -= y; if (x < 0) x += M; return x; }
inline int mul(int x, int y) { return ll(x) * y % M; }
struct Hash {
  int x = 0; ull y = 0;
  Hash() = default;
  Hash(int x, ull y): x(x), y(y) {}
  Hash(int x): x(x), y(x) {}
  Hash operator + (const Hash& h) const { return { sum(x, h.x), y + h.y}; }
  Hash operator - (const Hash& h) const { return { dif(x, h.x), y - h.y}; }
  Hash operator * (const Hash& h) const { return { mul(x, h.x), y * h.y}; }
  bool operator == (const Hash& h) const { return x == h.x && y == h.y; }
  friend ostream& operator << (ostream& os, Hash& h) {
    return os << '(' << h.x << ',' << h.y << ')';
  }
} base(31, 37);

const int N = 1e5 + 5;
Hash pre[N], suf[N], pw[N];
string s; int n;
Hash get(int l, int r) {
  if (l == 0 || r == 0 || l == n+1 || r == n+1)
    return 0;
  if (l <= r)
    return pre[r] - pre[l-1] * pw[r - l + 1];
  else
    return suf[r] - suf[l+1] * pw[l - r + 1];
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("trochoi.inp", "r"))
    freopen("trochoi.inp", "r", stdin),
    freopen("trochoi.out", "w", stdout);
  pw[0] = 1;
  for (int i = 1; i < N; ++i)
    pw[i] = pw[i-1] * base;
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> s, s = ' ' + s;
    for (int i = 1; i <= n; ++i)   
      pre[i] = pre[i-1] * base + Hash(s[i] - 'a' + 1);
    for (int i = n; i; --i)
      suf[i] = suf[i+1] * base + Hash(s[i] - 'a' + 1);
    vector<int> pos;
    for (int i = 1; i <= n; ++i) {
      Hash prefix = get(1, i-1) * pw[n-1 - (i-1)] + get(i+1, n);
      Hash suffix = get(n, i+1) * pw[n-1 - (n-i)] + get(i-1, 1);
      if (prefix == suffix) pos.emplace_back(i);
    }
    cout << pos.size() << '\n';
    for (int p : pos)
      cout << p-1 << ' ';
    cout << '\n';
  }
	return 0;
}


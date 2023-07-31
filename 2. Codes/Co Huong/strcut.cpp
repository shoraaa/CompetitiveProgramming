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
  vector<Hash> h;
  String() = default;
  String(const string& s) {
    n = s.size(); h.resize(n + 1);
    for (int i = 1; i <= n; ++i) 
      h[i] = h[i-1] * base + (s[i - 1] - 'a' + 1);
  }
  
  Hash get(int l, int r) {
    return h[r] - h[l - 1] * pw[r - l + 1];
  }
  
  friend istream& operator >> (istream& is, String& s) {
    string t; is >> t; s = String(t); return is;
  }
} s, t;
int n;
#define fi first
#define se second
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("strcut.inp", "r"))
    freopen("strcut.inp", "r", stdin),
    freopen("strcut.out", "w", stdout);
  pw[0] = 1;
  for (int i = 1; i < N; ++i)
    pw[i] = pw[i-1] * base;
  cin >> t >> s; n = s.n;
  Hash val = s.get(1, 2) * pw[3] + s.get(3, 3) * pw[2] + s.get(4, 5);
  int res = 0;
  for (int i = 1; i < s.n; ++i) for (int j = i+1; j < n; ++j) {
    // [1, i] , [i+1, j] , [j+1, n]
    pair<Hash, int> a[3] = {{s.get(1, i), i}, {s.get(i+1, j), j-i}, {s.get(j+1, n), n-j}};
    vector<int> d = {0, 1, 2};
    do {
      Hash val = 0;
      for (int i = 0; i < 3; ++i)
        val = val * pw[a[d[i]].se] + a[d[i]].fi;
      if (val == t.get(1, n)) {
        res++; break;
      }
    } while (next_permutation(d.begin(), d.end()));
  }
  cout << res;
	return 0;
}


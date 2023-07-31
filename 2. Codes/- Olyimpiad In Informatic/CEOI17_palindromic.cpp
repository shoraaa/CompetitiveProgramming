#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9 + 696969;
struct Hash {
  int x; unsigned long long y;
  Hash(int x = 0): x(x), y(x) {}
  friend Hash operator + (Hash u, const Hash& v) {
    u.x += v.x; u.y += v.y;
    if (u.x >= M) u.x -= M;
    return u;
  }
  friend Hash operator - (Hash u, const Hash& v) {
    u.x -= v.x; u.y -= v.y;
    if (u.x < 0) u.x += M;
    return u;
  }
  friend Hash operator * (Hash u, const Hash& v) {
    u.x = 1LL * u.x * v.x % M;
    u.y = u.y * v.y;
    return u;
  }
  friend bool operator == (const Hash& u, const Hash& v) {
    return u.x == v.x && u.y == v.y;
  }
};

using ull = Hash;

const int N = 1e6 + 5;

string s;

ull h[N], pw[N], base = 31;

ull get(int l, int r) {
  return h[r] - h[l - 1] * pw[r - l + 1];
}

int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  pw[0] = 1;
  for (int i = 1; i < N; ++i) {
    pw[i] = pw[i - 1] * base;
  }
  
  int T; cin >> T;
  while (T--) {
    cin >> s; 
    n = s.size();
    s = ' ' + s;
    
    for (int i = 1; i <= n; ++i) {
      h[i] = h[i - 1] * base + s[i] - 'a' + 1;
    }
    
    int last = 1, res = 0;
    for (int i = 1; i <= n / 2; ++i) {
      if (get(last, i) == get(n - i + 1, n - last + 1)) {
        res += 2;
        last = i + 1;
      }
    }
    if (last <= (n + 1) / 2) {
      res += 1;
    }
    cout << res << '\n';
    
  }
	return 0;
}


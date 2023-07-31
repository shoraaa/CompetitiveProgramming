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
  friend ostream& operator << (ostream& os, const Hash& h) {
    return os << '(' << h.x << ',' << h.y << ')';
  }
} base(31, 37);

const int N = 1e5 + 5;
Hash pre[N], pw[N];
vector<Hash> pret[N];

Hash get(int l, int r) {
  return pre[r] - pre[l-1] * pw[r - l + 1];
}
Hash get_t(int i, int l, int r) {
  return pret[i][r] - pret[i][l-1] * pw[r - l + 1];
}

string s, t[N];
int f[N], len[N];
int n, m;

int check(int k) {
  k += 1;
  // [i, n+i-1 + k-1] ko co vi tri nao la bat dau cua xau con dai k
  map<pair<int, ull>, bool> vis;
  for (int i = 0; i < m; ++i)
    for (int j = 1; j <= len[i]-k+1; ++j) {
      auto h = get_t(i, j, j+k-1);
      vis[{h.x, h.y}] = 1;
  }
  for (int i = 1; i <= n*2; ++i) {
    auto h = get(i, i+k-1);
    f[i] = f[i-1] + vis[{h.x, h.y}];
  } 
  for (int i = 1; i <= n*2-k+1; ++i)
    if (f[n+i-k] - f[i-1] == 0) 
      return 1;
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("minstr.inp", "r"))
    freopen("minstr.inp", "r", stdin),
    freopen("minstr.out", "w", stdout);
  
  pw[0] = 1;
  for (int i = 1; i < N; ++i)
    pw[i] = pw[i-1] * base;
  
  cin >> n >> m >> s; s = ' ' + s + s;
  for (int i = 1; i <= n*2; ++i)   
    pre[i] = pre[i-1] * base + Hash(s[i] - 'a' + 1);
  for (int i = 0; i < m; ++i) {
    cin >> t[i], len[i] = t[i].size(), t[i] = ' ' + t[i];
    pret[i].resize(len[i] + 1);
    for (int j = 1; j <= len[i]; ++j)
      pret[i][j] = pret[i][j-1] * base + Hash(t[i][j] - 'a' + 1);
  }
  int lo = 0, hi = n - 1, mid, ans = n;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid))
      ans = mid, hi = mid - 1;
    else
      lo = mid + 1;
  }
  cout << ans;
	return 0;
}


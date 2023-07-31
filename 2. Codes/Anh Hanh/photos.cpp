#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int _N = 1e5 + 5, N = 13 * _N + (1 << 18), M = 998244353;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}

int id = 0;
int sz[N], nxt[N][2], cnt[N][30];
vector<pair<int, int>> pos[30];

void add(int x) {
  int u = 0, cur = 0;
  for (int i = 29; ~i; --i) {
    int b = x >> i & 1; cur |= b * (1 << i);
    if (!nxt[u][b]) 
      nxt[u][b] = ++id, 
      pos[i].emplace_back(nxt[u][b], cur);
      
    u = nxt[u][b]; sz[u]++; 
    for (int j = i; ~j; --j) 
      if (x >> j & 1) cnt[u][j]++;
  }
}


int a[_N];
int n; ll m;

int find(int x, int h) {
  int u = 0;
  for (int i = 29; i >= h; --i) {
    int b = x >> i & 1;
    if (!nxt[u][b]) return 0;
    u = nxt[u][b];
  }
  return u;
}

ll count_pair(int h, int z) {
  ll res = 0;
  for (auto& p : pos[h]) {
    int u, x; tie(u, x) = p;
    int v = find(z ^ x, h);
    if (!v) continue;
    res += 1LL * sz[u] * sz[v];
  }
  return res / 2;
}

ll count_sum(int h, int z) {
  ll sum = 0;
  for (int i = 0; i < n; ++i) {
    int v = find(a[i] ^ z, h); 
    if (!v) continue;
    for (int j = h; ~j; --j) 
      if (a[i] >> j & 1) sum += (1LL << j) * (sz[v] - cnt[v][j]);
      else sum += (1LL << j) * cnt[v][j];
  }
  return sum / 2;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("photos.inp", "r")) 
    freopen("photos.inp", "r", stdin),
    freopen("photos.out", "w", stdout);
  cin >> n >> m; 
  for (int i = 0, x; i < n; ++i)
    cin >> a[i], add(a[i]);
    
  int cur = 0; ll sum = 0;
  for (int i = 29; ~i; --i) {
    // gia su dat 1
    ll cnt = count_pair(i, cur | (1 << i)); 
    if (cnt < m) {
      m -= cnt;
      sum += count_sum(i, cur | (1 << i)); 
    } else {
      cur |= 1 << i; sum += (1LL << i) * m;
    }
  }
  cout << sum % M;
	return 0;
}


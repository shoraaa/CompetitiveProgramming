#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1.6e6 + 5, M = 998244353;
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


int a[N];
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

ll inv2;

ll pw(ll x, ll k) {
  ll res = 1;
  for (; k; k >>= 1, x = x * x % M)
    if (k & 1) res = res * x % M;
  return res;
}

int count_sum(int h, int z) {
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    int v = find(a[i] ^ z, h);
    for (int j = h; ~j; --j) 
      if (a[i] >> j & 1) add(sum, (1LL << j) % M * (sz[v] - cnt[v][j]) % M);
      else add(sum, (1LL << j) % M * cnt[v][j] % M);
  }
  // int sum2 = 0;
  // for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) {
    // int x = a[i]^a[j]; 
    // if ((x >> h) == (z >> h)) add(sum2, x & ((1 << (h + 1)) - 1));
  // }
  return sum * inv2 % M;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("photos.inp", "r")) 
    freopen("photos.inp", "r", stdin),
    freopen("photos.out", "w", stdout);
  cin >> n >> m; inv2 = pw(2, M-2);
  for (int i = 0, x; i < n; ++i)
    cin >> a[i], add(a[i]);
    
  int cur = 0, sum = 0;
  for (int i = 29; ~i; --i) {
    // gia su dat 1
    ll cnt = count_pair(i, cur | (1 << i)); // dem so cap co tien to la cur + 1
    if (cnt < m) {
      m -= cnt;
      add(sum, count_sum(i, cur | (1 << i))); // tong moi cap xor co tien to la sum
    } else {
      cur |= 1 << i;
      add(sum, (1LL << i) % M * (m % M) % M);
    }
  }
  cout << sum;
	return 0;
}



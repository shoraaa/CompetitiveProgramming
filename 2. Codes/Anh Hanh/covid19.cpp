#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5, M = 998244353, inf = 1e9;

void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
void sub(int& x, int y) {
  x -= y; if (x < 0) x += M;
}
int dif(int x, int y) {
  x -= y; if (x < 0) x += M; return x;
}

int val[N * 2], sum[N * 2], lazy[N * 2];
ll P[N], C[N];

// Z (v - a[i]) * C^i <>  ZC^i * v - Z(a[i]*C^i)

int n, k, q, x, y, res, ans = 0; ll v; 

void build(int k = 1, int l = 1, int r = n) {
  if (l == r) return val[k] = M-1, sum[k] = -P[l] + M, add(ans, sum[k]), void();
  int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
  build(lc, l, m); build(rc, m+1, r);
  val[k] = min(val[lc], val[rc]); lazy[k] = -1;
  sum[k] = sum[lc]; add(sum[k], sum[rc]);
}

void push(int k, int lc, int rc, int l, int r, int m) {
  if (lazy[k] == -1) return; 
  int value = lazy[k]; lazy[k] = -1;
  sum[lc] = min(sum[lc], value); 
  sum[rc] = min(sum[rc], value);
  lazy[lc] = min(lazy[lc], value); 
  lazy[rc] = min(lazy[rc], value);
  sum[lc] = value * dif(C[m], C[l-1]) % M, 
  sum[rc] = value * dif(C[r], C[m]) % M; 
}

void update_point(int k, int l, int r) {
  if (l == r) {
    if (v >= val[k]) return;
    add(ans, dif(v, val[k]) * P[l] % M);
    val[k] = v; sum[k] = v * P[l] % M; return;
  }
  int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
  push(k, lc, rc, l, r, m); 
  if (x <= m) update_point(lc, l, m); 
  else update_point(rc, m+1, r);
  val[k] = min(val[lc], val[rc]); 
  sum[k] = sum[lc]; add(sum[k], sum[rc]);
}

void get_point(int k, int l, int r) {
  if (l == r) return res = min(res, val[k]), void();
  int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
  push(k, lc, rc, l, r, m); 
  if (x <= m) get_point(lc, l, m); 
  else get_point(rc, m+1, r);
}

void get(int k, int l, int r) {
  if (l > y || r < x) return;
  if (l >= x && r <= y) 
    return res = min(res, val[k]), void();
  int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
  push(k, lc, rc, l, r, m); get(lc, l, m); get(rc, m+1, r);
  
}

void update(int k, int l, int r) {
  if (l > y || r < x) return;
  if (l >= x && r <= y && v < val[k]) {
    sub(ans, sum[k]);
    add(ans, v * dif(C[r], C[l - 1]) % M);
    val[k] = lazy[k] = v; 
    sum[k] = v * dif(C[r], C[l - 1]) % M;
    return;
  }
  if (l == r) return;
  int m = l + r >> 1, lc = k+1, rc = k+(m-l+1)*2;
  push(k, lc, rc, l, r, m); update(lc, l, m); update(rc, m+1, r);
}


void update(int i, int val) {
  x = i, v = val;
  update_point(1, 1, n);
}

void Set(int l, int r, int val) {
  x = l, y = r, v = val;
  update(1, 1, n);
}

int get(int i) {
  x = i, res = inf;
  get_point(1, 1, n);
  return res;
}

int get(int l, int r) {
  x = l, y = r, res = inf;
  get(1, 1, n);
  return res;
}


int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("covid19.inp", "r"))
    freopen("covid19.inp", "r", stdin),
    freopen("covid19.out", "w", stdout);
  int T; cin >> T;
  cin >> n >> k >> q;
  
  P[0] = 1;
  for (int i = 1; i <= n; ++i)
    P[i] = P[i - 1] * (n + 1) % M,
    C[i] = C[i - 1] + P[i];
    
  build(); 
  for (int i = 0; i < k; ++i)
    cin >> x, update(x, 0);
  cout << ans << '\n'; 
  for (int i = 0; i < q; ++i) {
    char c; int u, v;
    cin >> c >> u >> v;
    if (c == 'D') {
      int min_val = min(get(u), get(v));
      if (min_val != inf) 
        update(u, min_val + 1), 
        update(v, min_val + 1);
    } else {
      int min_val = get(u, v);
      if (min_val != inf)
        Set(u, v, min_val + 1);
    }
    cout << ans << '\n';
  }
  
	return 0;
}


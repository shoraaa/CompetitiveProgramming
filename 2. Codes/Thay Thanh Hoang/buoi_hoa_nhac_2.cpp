#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 4e5 + 5;
int d[N], f[N], a[N], nxt[N][2], cur[N];
int n, m, k, p, id = 0;
ll b[N];

vector<int> fan;
int check(ll r) {
  int j = 1, k = 1;
  for (int i : fan) {
    j = max(j, i); k = max(k, j);
    while (j + 1 <= id * 2 && b[j + 1] <= r + b[i]) j++;
    while (k <= id * 2 && (a[k] == 0 || b[k] - r <= b[j])) k++;
    nxt[i][0] = k; 
  }
  
  for (int i : fan) cur[i] = i;
  for (int j = 0; j < 18; ++j) {
    int x = j & 1, y = x ^ 1;
    if (p >> j & 1) {
      for (int i : fan) if (i <= id) {
        cur[i] = nxt[cur[i]][x];
        if (cur[i] >= i + id) return 1;
      }
    }
    for (int i : fan) 
      nxt[i][y] = nxt[nxt[i][x]][x];
  }
  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> m >> k >> p;
  for (int i = 0, t, c; i < m; ++i)
    cin >> c >> t, 
    d[c] = t;
  for (int i = 0, u; i < k; ++i)
    cin >> u, f[u] = 1;
  
  ll cur_d = 0;
  for (int i = 1; i <= n; ++i) {
    cur_d += 1;
    if (d[i]) cur_d += d[i];
    else id++, a[id] = f[i], b[id] = cur_d, cur_d = 0;
  }
  
  for (int i = 1; i <= id; ++i)
    a[i + id] = a[i], b[i + id] = b[i];
  b[id + 1] += cur_d;
  for (int i = 1; i <= id * 2; ++i)
    b[i] += b[i - 1];
  
  a[id * 2 + 1] = 1;
  nxt[id * 2 + 1][0] = id * 2 + 1; 
  
  for (int i = 1; i <= id * 2 + 1; ++i)
    if (a[i]) fan.emplace_back(i);
  
  ll lo = 0, hi = 4e10 + 2e5, mid, ans = -1;
  while (lo <= hi) {
    mid = lo + hi >> 1;
    if (check(mid)) ans = mid, hi = mid - 1;
    else lo = mid + 1;
  }
  cout << ans;
	return 0;
}


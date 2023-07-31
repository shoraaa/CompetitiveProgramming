#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 5;
int a[N * 2], nxt[N * 2][20];
int n, k;
int check(int x) {
  int cur = 0; vector<int> cnt(30);
  auto insert = [&](int v) {
    for (int i = 29; ~i; --i) if (v >> i & 1) {
      if (cnt[i] == 0) cur ^= 1 << i;
      cnt[i]++;
    }
  };
  auto erase = [&](int v) {
    for (int i = 29; ~i; --i) if (v >> i & 1) {
      cnt[i]--;
      if (cnt[i] == 0) cur ^= 1 << i;
    }
  };
  for (int i = 0, j = 0; i < n*2; ++i) {
    while (j < n*2 && (cur & x) != x) insert(a[j]), j++;
    nxt[i][0] = j;
    erase(a[i]);
  }
  nxt[n * 2][0] = n * 2;
  for (int k = 1; k < 20; ++k) 
    for (int i = 0; i <= n*2; ++i)
      nxt[i][k] = nxt[nxt[i][k-1]][k-1];
  for (int i = 0; i < n; ++i) {
    int p = i;
    for (int b = 19; ~b; --b) if (k >> b & 1)
      p = nxt[p][b];
    if (p <= i + n) return 1;
  }
  return 0;
}
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
    cin >> a[i], a[i + n] = a[i];
  int res = 0;
  for (int i = 29; ~i; --i) 
    if (check(res | (1 << i))) res |= 1 << i;
  cout << res;
	return 0;
}
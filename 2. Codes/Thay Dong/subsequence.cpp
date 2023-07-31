#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 5, M = 1e9 + 7;
void add(int& x, int y) { x += y; if (x >= M) x -= M; }
int dif(int x, int y) { x -= y; if (x < 0) x += M; return x;}
int n, T;
int a[N], pos[N], dp[N], bit[N];
int get(int i) {
  int res = 0;
  for (i++; i; i -= i & -i)
    add(res, bit[i]);
  return res;
}
void update(int i, int x) {
  for (i++; i <= n + 1; i += i & -i)
    add(bit[i], x);
}
void erase(int i) {
  update(i, dif(get(i - 1), get(i)));
}
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("subsequence.inp", "r"))
    freopen("subsequence.inp", "r", stdin),
    freopen("subsequence.out", "w", stdout);
  cin >> n >> T;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  // dp[i] la so day con ket thuc tai i
  dp[0] = 1; update(0, 1);
  for (int i = 1, j, cur; i <= n; ++i) {
    if (j = pos[a[i]]) {
      cur = T == 1 ? get(i - 1) : dif(get(i - 1), get(j - 1));
      erase(j);
    } else {
      cur = get(i - 1);
    }
    update(i, cur);
    pos[a[i]] = i;
  }
  cout << dif(get(n), 1);
	return 0;
}


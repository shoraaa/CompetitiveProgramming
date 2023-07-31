#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int bit(int msk, int i) {
  return msk >> i & 1;
}
const int N = 1e5 + 5;
int a[N];
int n, A, O, X;
int solve() {
  for (int i = 0; i < n; ++i) a[i] = 0;
  for (int i = 29; ~i; --i) if (bit(A, i)) {
    if (!bit(O, i)) return 0;
    if (bit(X, i) && n % 2 == 0) return 0;
    if (!bit(X, i) && n % 2 == 1) return 0;
    for (int j = 0; j < n; ++j)
      a[j] |= 1 << i;
  } else {
    if (!bit(X, i) && !bit(O, i)) continue;
    if (bit(X, i) && !bit(O, i)) return 0;
    if (bit(X, i)) {
      if (n <= 1) return 0;
      a[0] |= 1 << i;
    } else {
      if (n <= 2) return 0;
      a[0] |= 1 << i, a[1] |= 1 << i;
    }
  }
  return 1;
}
int main() {
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> A >> O >> X;
    if (solve()) {
      for (int i = 0; i < n; ++i)
        cout << a[i] << " \n"[i == n-1];
    } else {
      cout << -1 << '\n';
    }
  }
	return 0;
}


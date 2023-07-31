#include<bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 20;
int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int T = 1;
  cout << T << '\n';
  while (T--) {
    int n = rng() % N + 1, m = rng() % n + 1;
    cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; ++i)
      cout << rng() % N + 1 << ' ';
    cout << '\n';
    for (int i = 0; i < m; ++i) {
      int r = rng() % n + 1, l = rng() % r + 1;
      cout << l << ' ' << r << '\n';
    }
    cout << '\n';
  }
	return 0;
}


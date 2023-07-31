#include<bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 5000 + 5;
int main() {
	cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  int n = rng() % N + 1, k = rng() % n + 1;
  cout << n << ' ' << k << '\n';
  for (int i = 0; i < n; ++i)
    cout << rng() % N + 1 << ' ';
	return 0;
}


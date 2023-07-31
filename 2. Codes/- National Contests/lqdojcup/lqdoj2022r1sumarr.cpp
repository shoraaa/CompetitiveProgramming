#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9 + 7;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}
void sub(int& x, int y) {
  x -= y; if (x < 0) x += M;
}

const int N = 2e5 + 5;
int f[N];
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i) 
    cin >> f[i];
  for (int i = 0; i < 18; ++i) 
    for (int msk = 0; msk < n; ++msk) 
      if (msk >> i & 1) add(f[msk], f[msk ^ (1 << i)]);
  for (int i = 0; i < n; ++i)
    f[i] = 1LL * f[i] * f[i] % M;
  for (int i = 0; i < 18; ++i) 
    for (int msk = 0; msk < n; ++msk)
      if (msk >> i & 1) sub(f[msk], f[msk ^ (1 << i)]);
  for (int i = 0; i < n; ++i)
    cout << f[i] << ' ', add(f[i + 1], f[i]);
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int M = 1e9 + 7;
void add(int& x, int y) {
  x += y; if (x >= M) x -= M;
}

const int N = 2e5 + 5;
int a[N], f[N];
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0; i < n; ++i) {
    add(f[i], ll(a[i]) * a[i] % M); 
    for (int j = i + 1; j < n; ++j) 
      add(f[i | j], 2LL * a[i] * a[j] % M);
  }
  for (int msk = 0; msk < n; ++msk) { 
    add(f[msk], f[msk - 1]);
    cout << f[msk] << ' ';
  }
	return 0;
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5, M = 998244353;
int cnt[8][10];
int n;

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  if (fopen("numdist.inp", "r")) 
    freopen("numdist.inp", "r", stdin);
    freopen("numdist.out", "w", stdout);
   
  cin >> n;
  for (int i = 0, x; i < n; ++i) {
    cin >> x;
    for (int j = 0; j < 8; ++j) {
      int d = x % 10; x /= 10;
      cnt[j][d]++;
    }
  }
  int res = 0;
  for (int i = 0; i < 8; ++i) {
    int sum = 0;
    for (int d = 0; d < 10; ++d) sum += cnt[i][d];
    for (int d = 0; d < 10; ++d) {
      sum -= cnt[i][d];
      res += 1LL * cnt[i][d] * sum % M;
      if (res >= M) res -= M;
    }
  }
  cout << res;
	return 0;
}


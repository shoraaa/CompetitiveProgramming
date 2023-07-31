#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 5;
int spt[N][19];
int n, q;

int get(int l, int r) {
  int k = __lg(r - l + 1);
  return min(spt[l][k], spt[r - (1 << k) + 1][k]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0); cout.tie(0);
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> spt[i][0];
  }
  
  for (int j = 1; j <= 18; ++j) {
    for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
      spt[i][j] = min(spt[i][j - 1], spt[i + (1 << (j - 1))][j - 1]);
    }
  }
  
  for (int i = 1, l, r; i <= q; ++i) {
    cin >> l >> r; l++;
    cout << get(l, r) << '\n';
  }
  
	return 0;
}

